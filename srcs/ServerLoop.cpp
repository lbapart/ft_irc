#include "../incl/Server.hpp"
#include <algorithm>

int	Server::pollinEvent(const int &fd, std::vector<pollfd> &fds)
{
	if (fd == this->_socket) // if socket fd is triggered, then new client tries to connect
	{
		std::cout << "New Client tries to connect!\n" << std::endl;
		int	newClientFd = connectClient();
		if (newClientFd == -1)
			return (ERROR);
		else
			fds.push_back({newClientFd, POLLIN | POLLOUT, 0});
	}
	else // if client fd is triggered, then client sent a message
	{
		std::cout << "Client sent a message!\n" << std::endl;
		std::string message;
		if (getClientMessage(fd, message) == ERROR)
			return (ERROR);
		std::cout << "Message: " << message << std::endl;
	}
	return (SUCCESS);
}

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
		std::vector<pollfd>	temp;

		if (poll(this->_fds.data(), this->_fds.size(), -1) == -1) {
			std::cerr << "Poll error" << std::endl;
			throw PollException();
		}

		std::vector<pollfd>::iterator it = this->_fds.begin();
		while (it != this->_fds.end())
		{
			if (it->revents & POLLIN)
			{
				if (this->pollinEvent(it->fd, temp) == ERROR)
					continue ;
			}
			else if (it->revents & POLLOUT)
			{
				// std::cout << "Client is ready to receive a message" << std::endl;
			}
			else if (it->revents & POLLHUP)
			{
				std::cout << "Connection closed" << std::endl;
			}
			++it;
		}

		this->_fds.insert(this->_fds.end(), temp.begin(), temp.end());
	}
}
