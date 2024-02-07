#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

void Client::kick(const std::string & nickname)
{

    if (this->_channel == NULL)
    {
        this->_server->sendResponse(this->iSocket, "442 :You're not in a channel");
        return;
    }
    if (this->_channel->getOperators().count(this->iSocket) == 0)
	{
		this->_server->sendResponse(this->iSocket, "482 " + this->_channel->getName() + " :You're not a channel operator");
		return;
	}

	int fd = this->_server->getClientIdByNickname(nickname);
	//TODO: refactor this
	if (fd > 0)
	{
		if (this->_channel->getClients().count(fd) > 0)
		{
			this->_channel->removeClient(this->_server->getClients()[fd]);
			this->_channel->removeOperator(this->_server->getClients()[fd]);
			this->_server->sendResponse(fd, "KICK " + this->_channel->getName() + " " + nickname + " :You have been kicked from the channel");
			this->_server->sendResponse(this->iSocket, "KICK " + this->_channel->getName() + " " + nickname + " :You have kicked " + nickname + " from the channel");
			return;
		}
	}
	this->_server->sendResponse(this->iSocket, "441 " + nickname + " " + this->_channel->getName() + " :They aren't on that channel");
}
