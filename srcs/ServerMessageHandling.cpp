#include "General.hpp"

int	Server::getClientMessage(int fd, std::string &message)
{
	char		buffer[1024];

	std::memset(buffer, 0, 1024);

	int bytesRead = recv(fd, buffer, 1024, 0);
	if (bytesRead < 0)
	{
		std::cerr << "Error occured during communication with client" << std::endl;
		this->_clients.erase(fd);
		for (std::vector<pollfd>::iterator it = this->_fds.begin(); it != this->_fds.end(); it++)
		{
			if (it->fd == fd)
			{
				this->_fds.erase(it);
				break ;
			}
		}
		close(fd);
		return (ERROR);
	}
	else if (bytesRead == 0)
	{
		std::cout << "Client disconnected" << std::endl; // TODO: createfunction for deleting user form db
		this->_clients.erase(fd);
		for (std::vector<pollfd>::iterator it = this->_fds.begin(); it != this->_fds.end(); it++)
		{
			if (it->fd == fd)
			{
				this->_fds.erase(it);
				break ;
			}
		}
		close(fd);
		return (ERROR);
	}
	else
	{
		message = buffer;
		return (SUCCESS);
	}
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
