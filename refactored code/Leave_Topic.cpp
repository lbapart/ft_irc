#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

void Client::leave()
{
    if (this->_channel == NULL)
    {
        this->_server->sendResponse(this->iSocket, "442 :You're not in a channel");
        return;
    }
    this->_channel->removeClient(*this);
    this->_server->sendResponse(this->iSocket, "PART " + this->_channel->getName());
    this->_channel = NULL;
}

void Client::topic(const std::string& topic)
{
    if (this->_channel == NULL)
    {
        this->_server->sendResponse(this->iSocket, "442 :You're not in a channel");
        return;
    }
    if (this->_channel->isTopicOperatorProtected() && this->_channel->getOperators().find(this->_nickname) == this->_channel->getOperators().end())
    {
        this->_server->sendResponse(this->iSocket, "482 " + this->_channel->getName() + " :You're not a channel operator");
        return;
    }
    this->_channel->setTopic(topic);
    this->_server->sendResponse(this->iSocket, "332 " + this->_channel->getName() + " :" + topic);
    this->_server->sendResponse(this->iSocket, "TOPIC " + this->_channel->getName() + " :" + topic);
}
