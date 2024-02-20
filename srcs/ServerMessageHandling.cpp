#include "General.hpp"

int	Server::getClientMessage(int fd, std::string &message)
{
	char		buffer[1024];

	std::memset(buffer, 0, 1024);

	int bytesRead = recv(fd, buffer, 1023, 0);
	if (bytesRead <= 0)
	{
		std::cout << "Client disconnected" << std::endl;
		this->deleteClient(fd);
		return (ERROR);
	}
	else
	{
		buffer[bytesRead] = '\0';
		message = buffer;
		std::cout << "[Message received]: " << message << std::endl;
		return (SUCCESS);
	}
}

void		Server::flushResponse(int fd)
{
	if (fd == -1)
		return ;
	if (this->getClient(fd).getOutputBuffer().empty())
		return ;

	int bytesSent = 0;
	std::cout << "[Sending]: " << this->getClient(fd).getOutputBuffer() << std::endl;
	std::string response = this->getClient(fd).getOutputBuffer();
	this->getClient(fd).setOutputBuffer("");
	while (bytesSent < (int)response.size())
	{
		int sent = send(fd, response.c_str() + bytesSent, response.size() - bytesSent, 0);
		if (sent == -1)
		{
			std::cout << "Can't send response to a client" << std::endl;
			break ;
		}
		bytesSent += sent;
	}

}

void		Server::prepareResponse(int fd, const std::string& response)
{
	if (fd == -1)
		return ;
	this->getClient(fd).setOutputBuffer(this->getClient(fd).getOutputBuffer() + response);
}
