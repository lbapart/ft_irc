#include "General.hpp"


// TODO this should be modified
void Client::sendToChannel(const std::string &message)
{
	if (this->_channel == NULL)
		return;

	for (std::set<int>::iterator it = this->_channel->getClients().begin(); it != this->_channel->getClients().end(); ++it)
	{
		this->_server->sendResponse(*it, message);
	}
}

void Client::sendToUser(const std::string &nickname, const std::string &message)
{
	int fd = this->_server->getClientIdByNickname(nickname);
	std::map<int, Client>::iterator it = this->_server->getClients().find(fd);
	if (it != this->_server->getClients().end())
		this->_server->sendResponse(it->second.getISocket(), message);
	// TODO send error message
}
