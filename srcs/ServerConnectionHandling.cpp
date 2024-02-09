#include "Server.hpp"

int	Server::addClient()
{
	sockaddr_in clientAddr;
	socklen_t	clientAddrLen = sizeof(clientAddr);

	int fd = accept(this->_socket, (struct sockaddr *)&clientAddr, &clientAddrLen);
	if (fd == -1)
		return (fd);

	this->_clients.insert(std::pair<int, Client>(fd, Client(fd, this)));

	return (fd);
}
