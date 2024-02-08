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
			this->_server->sendResponse(this->iSocket, Response::OKkickSuccess(nickname, this->_channel->getName()));
			this->_server->sendResponse(fd, Response::YouWereKicked(nickname, this->_channel->getName()));
			for (std::set<int>::iterator it = this->_channel->getClients().begin(); it != this->_channel->getClients().end(); ++it)
			{
				this->_server->sendResponse(*it, Response::UserLeftChannel(nickname, this->_channel->getName()));
			}
			return;
		}
	}
	this->_server->sendResponse(this->iSocket, Response::ERRkickFailed(nickname, this->_channel->getName()));
}
