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

void	Server::clientConnected()
{
	char buffer[1024];
	int bytesRead;
	newConnection newClient;
	sockaddr_in clientAddr;
	socklen_t	clientAddrLen = sizeof(clientAddr);

	int fd = accept(this->_socket, (struct sockaddr *)&clientAddr, &clientAddrLen);
	if (fd == -1)
		throw AcceptException();
	bytesRead = recv(fd, buffer, 1024, 0);
	buffer[bytesRead] = 0;
	std::cout << "DATA READ FROM THE FIRST CLIENT:" << std::endl;
	std::cout << buffer << std::endl;
	//TODO: parse the data from the client
	//// function to parse the data from the client to be added here
	//TODO: authentificate the client
/* 	if (authentificateConnection(newClient))
		return(clientDisconnected(fd));
	this->_fds.push_back({fd, POLLIN, 0});
	Client validatedClient(newClient);
	this->_clients[newClient.sSocket] = validatedClient; */
	std::cout << fd << std::endl;
	std::cout << "New client connected" << std::endl;
	//response to the client about the connection
	std::string response = "Welcome to the server created by Vfrants, Aapenko and Rkurnava \r\n";
	sendResponse(fd, response);
}

void	Server::clientDisconnected(int fd)
{
	std::cout << "Client fd erased" << std::endl;
	close(fd);
	this->_fds.erase(std::remove_if(this->_fds.begin(), this->_fds.end(), [fd](const pollfd& pfd) { return pfd.fd == fd; }), this->_fds.end());
}
