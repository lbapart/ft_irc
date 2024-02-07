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
    std::map<std::string, Client>::iterator Operator = this->_channel->getOperators().find(this->_nickname);
    if (Operator == this->_channel->getOperators().end())
    {
        this->_server->sendResponse(this->iSocket, "482 " + this->_channel->getName() + " :You're not a channel operator");
        return;
    }
    std::map<std::string, Client>::iterator _client = this->_server->getClients().find(nickname);
    if (_client == this->_server->getClients().end())
    {
        this->_server->sendResponse(this->iSocket, "401 " + nickname + " :No such nickname");
        return;
    }
    this->_channel->removeClient(_client->second);
    this->_server->sendResponse(this->iSocket, "KICK " + this->_channel->getName() + " " + nickname);
}
