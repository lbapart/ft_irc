#include "Server.hpp"

//Constructor && Destructor

Server::Server(ushort port, const std::string& password)
{
	this->_port = port;
	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socket == -1)
		throw SocketCreationException();
	int flags = fcntl(this->_socket, F_SETFL, O_NONBLOCK);
	if (flags == -1)
		throw SocketCreationException();

	int opt = 1;
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw SocketCreationException();
	this->_password = password;

	struct pollfd pfd;
	pfd.fd = this->_socket;
	pfd.events = POLLIN;
	pfd.revents = 0;
	this->_fds.push_back(pfd);
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(this->_port);
	this->_addr.sin_addr.s_addr = INADDR_ANY;
}

Server::~Server()
{
	close(this->_socket);
}
/////////////////////////////////////////////////////////////////////////////////////////////////

//Exceptions

const char* Server::SendException::what() const throw()
{
	return "Send failure";
}

const char* Server::PollException::what() const throw()
{
	return "Poll failure";
}

const char*	Server::SocketCreationException::what() const throw()
{
	return "Socket creation failure";
}

const char*	Server::SocketBindException::what() const throw()
{
	return "Socket bind failure";
}

const char*	Server::SocketListenException::what() const throw()
{
	return "Socket listen failure";
}

const char*	Server::AcceptException::what() const throw()
{
	return "Socket accept failure";
}

std::string		Server::getPassword() const
{
	return this->_password;
}

Client&			Server::getClient(int fd)
{
	return this->_clients[fd];
}

Channel*		Server::addChannel(const std::string& channelName, const std::string& password, const int& fd)
{
	this->_channels[channelName] = Channel(channelName, password, fd, this);
	return &this->_channels[channelName];
}

void		Server::removeChannel(const std::string& channelName)
{
	this->_channels.erase(channelName);
}

Channel*	Server::getChannel(const std::string& channelName)
{
	if (this->_channels.find(channelName) == this->_channels.end())
		return NULL;
	return &this->_channels[channelName];
}
