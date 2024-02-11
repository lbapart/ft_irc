#include "General.hpp"
#include <cstddef>

int	Server::getClientMessage(int fd, std::string &message)
{
	char		buffer[1024];

	std::memset(buffer, 0, 1024);

	int bytesRead = recv(fd, buffer, 1024, 0);
	if (bytesRead <= 0)
	{
		this->deleteClient(fd);
		return (ERROR);
	}
	else
	{
		message = buffer;
		return (SUCCESS);
	}
}

void		Server::flushResponse(int fd)
{
	if (this->getClient(fd).getBuffer().empty())
		return ;

	int bytesSent = 0;
	std::cout << "Sending: " << this->getClient(fd).getBuffer() << std::endl;
	std::string response = this->getClient(fd).getBuffer();
	this->getClient(fd).setBuffer("");
	while (bytesSent < (int)response.size())
	{
		int sent = send(fd, response.c_str() + bytesSent, response.size() - bytesSent, 0);
		if (sent == -1)
			throw SendException(); //here
		bytesSent += sent;
	}

}

void		Server::prepareResponse(int fd, const std::string& response)
{
	this->getClient(fd).setBuffer(this->getClient(fd).getBuffer() + response);
}
