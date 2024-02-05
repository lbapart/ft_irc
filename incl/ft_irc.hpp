#ifndef FT_IRC_HPP
# define FT_IRC_HPP


# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <cstdlib>
# include <exception>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <sys/poll.h>
# include <fcntl.h>
# include <cstring>
# include <algorithm>

# define ERROR 1
# define SUCCESS 0

class Client;

class Channel
{
	private:
		std::string							_name;
		std::string							_password;
		std::map<std::string, Client>		_clients;
		std::map<std::string, Client>		_operators;
	public:
		Channel(std::string name, const std::string& password);
		~Channel();
		void join(int client);
		void leave(int client);
		void send(int client, const std::string& message);
};

Channel::Channel(std::string name, const std::string& password)
{
	this->_name = name;
	this->_password = password;
}

Channel::~Channel()
{
}

class Client
{
	private:
		int								_socket;
		std::string						_nickname;
		std::string						_password;
		std::map<std::string, Channel> 	_channels;
	public:
		Client(int socket, const std::string& password);
		~Client();
		void join(const std::string& channel, const std::string& password);
		void leave(const std::string& channel);
		void send(const std::string& channel, const std::string& message);
};

Client::Client(int socket, const std::string& password)
{
	this->_socket = socket;
	this->_password = password;
}

Client::~Client()
{
}

class Server
{
	private:
		ushort								_port;
		int									_socket;
		std::string							_password;
		struct sockaddr_in					_addr;
		std::vector<pollfd>					_fds;
		// std::map<std::string, Channel>		_channels;
		// std::map<std::string, Client>		_clients;
	public:
		class SocketCreationException : public std::exception
		{
			public:
				virtual const char* what() const throw();				
		};
		class SocketBindException : public std::exception
		{
			public:
				virtual const char* what() const throw();				
		};
		class SocketListenException : public std::exception
		{
			public:
				virtual const char* what() const throw();				
		};
		class PollException : public std::exception
		{
			public:
				virtual const char* what() const throw();				
		};
		class AcceptException : public std::exception
		{
			public:
				virtual const char* what() const throw();				
		};
		class SendException : public std::exception
		{
			public:
				virtual const char* what() const throw();				
		};
		Server(ushort port, const std::string& password);
		~Server();
		void		run();
		void		clientConnected();
		std::string	getClientMessage(int fd);
		void		clientDisconnected(int fd);
		void		sendResponse(int fd, const std::string& response);

};

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

#endif