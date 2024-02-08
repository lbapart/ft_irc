#include "Server.hpp"
#include <vector>


int	Server::getClientMessage(int fd, std::string &message)
{
	char		buffer[1024];

	std::memset(buffer, 0, 1024);

	// std::cout << "Client fd" << fd << std::endl;
	int bytesRead = recv(fd, buffer, 1024, 0);
	// std::cout << "BYTES READ: " << bytesRead << std::endl;
	if (bytesRead == -1)
		std::cerr << "Error reading from client" << std::endl;
	if (bytesRead <= 0) {
		this->_clients.erase(fd);
		for (std::vector<pollfd>::iterator it = this->_fds.begin(); it != this->_fds.end(); it++)
		{
			if (it->fd == fd)
			{
				this->_fds.erase(it);
				break ;
			}
		}
		// this->_fds.erase(fd);  //TODO: delete client from db -----------------------------
		close(fd);
		return (-1);
	}

	t_request _req;
	int status = parseLines(_req, buffer, fd);
	// std::cout << "BUFFER: " << buffer << std::endl;
	message = buffer;
	std::string response = ":server 001 aapenko :Welcome to the server\r\n";
	send(fd, response.c_str(), response.size(), 0);
	return status;
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
