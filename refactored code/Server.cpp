#include "Server.hpp"

void	Server::clientDisconnected(int fd)
{
	close(fd);
	this->_fds.erase(std::remove_if(this->_fds.begin(), this->_fds.end(), [fd](const pollfd& pfd) { return pfd.fd == fd; }), this->_fds.end());
}

std::string	Server::getClientMessage(int fd)
{
	char		buffer[1024];
	std::string	message;

	std::cout << "Reading message" << std::endl;
	while (1)
	{
		std::memset(buffer, 0, 1024);
		int bytesRead = recv(fd, buffer, sizeof(buffer), 0);
		std::cout << bytesRead << std::endl;
		if (bytesRead == -1)
		{
			if (errno == EWOULDBLOCK || errno == EAGAIN)
				continue ;
			else
				throw AcceptException();
		}
		if (bytesRead == 0)
			break;
		message.append(buffer);
		if (std::strstr(buffer, "\n") != NULL)
			break;
	}
	std::cout << message << std::endl;
	std::cout << "Message read" << std::endl;
	std::cout.flush();
	std::string response = ":server 001 aapenko :Welcome to the server\r\n";
	send(fd, response.c_str(), response.size(), 0);
	return message;
}

void		Server::sendResponse(int fd, const std::string& response)
{
	int bytesSent = 0;
	while (bytesSent < response.size())
	{
		int sent = send(fd, response.c_str() + bytesSent, response.size() - bytesSent, 0);
		if (sent == -1)
		{
			if (errno == EWOULDBLOCK || errno == EAGAIN)
				continue ;
			else
				throw SendException();
		}
		bytesSent += sent;
	}
}

void	Server::clientConnected()
{
	sockaddr_in clientAddr;
	socklen_t	clientAddrLen = sizeof(clientAddr);

	int fd = accept(this->_socket, (struct sockaddr *)&clientAddr, &clientAddrLen);
	if (fd == -1)
		throw AcceptException();
	
	this->_fds.push_back({fd, POLLIN, 0});

	std::string response = "Welcome to the server\r\n";
	sendResponse(fd, response);
	std::cout << "New connection" << std::endl;
}


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

Server::~Server()
{
	close(this->_socket);
}

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
	this->_fds.push_back({this->_socket, POLLIN, 0});
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(this->_port);
	this->_addr.sin_addr.s_addr = INADDR_ANY;
}


void	Server::run()
{
	if (bind(this->_socket, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) == -1)
		throw SocketBindException();
	//TODO think about number of clients
	if (listen(this->_socket, 10) == -1)
		throw SocketListenException();
	while (1)
	{
		if (poll(this->_fds.data(), this->_fds.size(), -1) == -1)
			throw PollException();
		for (std::vector<pollfd>::iterator it = this->_fds.begin(); it != this->_fds.end(); it++)
		{
			if (!it->revents)
				continue;
			if (it->revents & POLLIN)
			{
				std::cout << it->fd << std::endl;
				if (it->fd == this->_socket)
				{
					std::cout << "hello" << std::endl;
					clientConnected();
					break;
				}
				else
				{
					std::string message = getClientMessage(it->fd);
					if (message.empty())
					{
						clientDisconnected(it->fd);
						break;
					}
				}
			}
			if (it->revents & POLLHUP)
			{
				std::cout << "Connection closed" << std::endl;
			}
		}
	}
}
