#ifndef SERVER_HPP
# define SERVER_HPP

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
# include <sstream>
# include <iomanip>
# include <ctime>
# include <chrono>
# include <limits>

# include <cerrno>

# include "General.hpp"
# include "Channel.hpp"
# include "Client.hpp"

class Server
{
	private:
		ushort								_port;
		int									_socket;
		std::string							_password;
		struct sockaddr_in					_addr;
		std::vector<pollfd>					_fds;
		std::map<std::string, Channel>		_channels;
		std::map<std::string, Client>		_clients;
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
		int			authentificateConnection(struct newConnection& newClient);
};

#endif
