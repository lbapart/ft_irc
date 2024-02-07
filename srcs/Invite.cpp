#include "General.hpp"

void Client::invite(const std::string &nickname)
{
    if (this->_channel == NULL)
    {
        this->_server->sendResponse(this->iSocket, Response::ERRinviteFailed(nickname, this->_channel->getName()));
        return;
    }
    std::map<int, Client>::iterator _client = this->_server->getClients().find(this->iSocket);
    if (_client == this->_server->getClients().end())
    {
        this->_server->sendResponse(this->iSocket, Response::ERRinviteFailed(nickname, this->_channel->getName()));
        return;
    }
    std::map<std::string, Channel>::iterator _channel = this->_server->getChannels().find(this->_channel->getName());
    _channel->second.addClient(_client->second);
	this->_server->sendResponse(this->iSocket, Response::OKinviteSuccess(nickname, this->_channel->getName()));
}
