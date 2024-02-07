#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

void Client::invite(const std::string &nickname)
{
    if (this->_channel == NULL)
    {
        this->_server->sendResponse(this->iSocket, "442 :You're not in a channel");
        return;
    }
    std::map<int, Client>::iterator _client = this->_server->getClients().find(this->iSocket);
    if (_client == this->_server->getClients().end())
    {
        this->_server->sendResponse(this->iSocket, "401 " + nickname + " :No such nickname");
        return;
    }
    std::map<std::string, Channel>::iterator _channel = this->_server->getChannels().find(this->_channel->getName());
    _channel->second.addClient(_client->second);
}
