#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

void Client::sendToAll(const std::string &message)
{
    std::map<std::string, Client>::iterator it = this->_server->getClients().begin();
    while (it != this->_server->getClients().end())
    {
        this->_server->sendResponse(it->second.getISocket(), message);
        it++;
    }
}

void Client::sendToUser(const std::string &nickname, const std::string &message)
{
    std::map<std::string, Client>::iterator it = this->_server->getClients().find(nickname);
    if (it != this->_server->getClients().end())
        this->_server->sendResponse(it->second.getISocket(), message);
}
