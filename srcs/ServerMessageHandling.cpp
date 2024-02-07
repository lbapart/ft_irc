#include "Server.hpp"

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
	while (bytesSent < (int)response.size())
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
