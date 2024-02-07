#include "General.hpp"

void Client::kick(const std::string & nickname)
{

    if (this->_channel == NULL)
    {
        this->_server->sendResponse(this->iSocket, Response::ERRkickFailed(nickname, this->_channel->getName()));
        return;
    }
    if (this->_channel->getOperators().count(this->iSocket) == 0)
	{
		this->_server->sendResponse(this->iSocket, Response::ERRkickFailed(nickname, this->_channel->getName()));
		return;
	}

	int fd = this->_server->getClientIdByNickname(nickname);
	if (fd > 0)
	{
		if (this->_channel->getClients().count(fd) > 0)
		{
			this->_channel->removeClient(this->_server->getClients()[fd]);
			this->_channel->removeOperator(this->_server->getClients()[fd]);
			//TODO: kick message for a client
			this->_server->sendResponse(fd, "KICK " + this->_channel->getName() + " " + nickname + " :You have been kicked from the channel");
			this->_server->sendResponse(this->iSocket, Response::OKkickSuccess(nickname, this->_channel->getName()));
			return;
		}
	}
	this->_server->sendResponse(this->iSocket, "441 " + nickname + " " + this->_channel->getName() + " :They aren't on that channel");
}
