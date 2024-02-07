#include "General.hpp"

void	Server::run()
{
	if (bind(this->_socket, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) == -1)
		throw SocketBindException();
	//TODO think about number of clients
	//listen function limits the number of pending connections
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
					std::cout << "New Client tries to connect!" << std::endl;
					clientConnected();
					break;
				}
				else
				{
					std::string message = getClientMessage(it->fd);
					if (message == "/QUIT" || message == "/quit" || message == "/Quit")
					{
						clientDisconnected(it->fd);
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
