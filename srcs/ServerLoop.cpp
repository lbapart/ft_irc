#include "../incl/Server.hpp"
#include <algorithm>

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
			// std::cout << "loop run" << std::endl;
			if (it->revents & POLLIN)
			{
				// std::cout << it->fd << std::endl;
				// std::cout << "Socket fd = " << this->_socket << std::endl;
				if (it->fd == this->_socket)
				{
					std::cout << "New Client tries to connect!" << std::endl;
					int	fd = clientConnected();
					if (fd == -1)
						continue ;
					temp.push_back({fd, POLLIN | POLLOUT, 0});
				}
				else
				{
					std::cout << "Client sent a message\n" << std::endl;
					std::string message;
					int status = getClientMessage(it->fd, message);
					if (status == -1) {
						std::cout << "BREAK" << std::endl;
						break;
					}
				}
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
