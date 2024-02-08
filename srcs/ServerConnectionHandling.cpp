#include "Server.hpp"

int Server::authentificateConnection(newConnection& newClient)
{
	if (this->_password == newClient._password)
	{
		std::cout << "Client authentificated" << std::endl;
		return (SUCCESS);
	}
	else
	{
		std::cout << "Client not authentificated, invalid password!" << std::endl;
		return (ERROR);
	}
}

int	Server::clientConnected()
{
	sockaddr_in clientAddr;
	socklen_t	clientAddrLen = sizeof(clientAddr);

	int fd = accept(this->_socket, (struct sockaddr *)&clientAddr, &clientAddrLen);
	if (fd == -1)
		return (fd);

	std::string response = "Welcome to the server created by Vfrants, Aapenko and Rkurnava \r\n";
	sendResponse(fd, response);

	return (fd);
}

void	Server::clientDisconnected(int fd)
{
	std::cout << "Client fd erased" << std::endl;
	close(fd);
	for (std::vector<pollfd>::iterator it = this->_fds.begin(); it != this->_fds.end(); )
	{
    	if (it->fd == fd)
        	it = this->_fds.erase(it);
    	else
        	++it;
	}
}
