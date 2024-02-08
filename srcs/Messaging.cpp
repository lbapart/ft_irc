#include "General.hpp"


// TODO this should be modified
void Client::sendToChannel(const std::string &message)
{
	if (this->_channel == NULL)
	{
		this->_server->sendResponse(this->iSocket, Response::ERRmessageFailed(this->getNickname(), this->_channel->getName()));
		return;
	}
	if (this->_channel->getClients().count(this->iSocket) == 0)
	{
		this->_server->sendResponse(this->iSocket, Response::ERRmessageFailed(this->getNickname(), this->_channel->getName()));
		return;
	}
	for (std::set<int>::iterator it = this->_channel->getClients().begin(); it != this->_channel->getClients().end(); ++it)
	{
		this->_server->sendResponse(*it, Response::MessageToChannel(this->getNickname(), this->_channel->getName(), message));
	}
}

void Client::sendToUser(const std::string &nickname, const std::string &message)
{
	int fd = this->_server->getClientIdByNickname(nickname);
	std::map<int, Client>::iterator it = this->_server->getClients().find(fd);
	if (it != this->_server->getClients().end())
	{
		this->_server->sendResponse(fd, Response::MessageToUser(this->getNickname(), message));
		return;
	}
	this->_server->sendResponse(this->iSocket, Response::ERRprivateMessageFailed(this->getNickname(), nickname));
}
