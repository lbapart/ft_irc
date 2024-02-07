#include "General.hpp"

//TODO: refactor response messages
void Client::join(const std::string& channel, const std::string& password)
{
    std::map<std::string, Channel>::iterator _channel = this->_server->getChannels().find(channel);
    if (_channel == this->_server->getChannels().end())
    {
		this->_server->createChannel(channel, password, *this);
        return;
    }
    if (_channel->second.isInviteOnly() && _channel->second.getClients().find(this->iSocket) == _channel->second.getClients().end())
    {
        this->_server->sendResponse(this->iSocket, "473 " + channel + " :Cannot join channel (+i)");
        return;
    }
    if (_channel->second.isPasswordProtected() && _channel->second.getPassword() != password)
    {
        this->_server->sendResponse(this->iSocket, "475 " + channel + " :Wrong password");
        return;
    }
    else if (_channel->second.isPasswordProtected() && _channel->second.getPassword() == password)
    {
        _channel->second.addClient(*this);
        this->_channel = &_channel->second;
        this->_server->sendResponse(this->iSocket, "JOIN " + channel);
        this->_server->sendResponse(this->iSocket, "332 " + channel + " :" + _channel->second.getTopic());
        this->_server->sendResponse(this->iSocket, "353 " + channel + " = " + channel + " :" + _channel->second.getClientsList());
        this->_server->sendResponse(this->iSocket, "366 " + channel + " :End of /NAMES list");
    }
    else
    {
        _channel->second.addClient(*this);
        this->_channel = &_channel->second;
        this->_server->sendResponse(this->iSocket, "JOIN " + channel);
        this->_server->sendResponse(this->iSocket, "332 " + channel + " :" + _channel->second.getTopic());
        this->_server->sendResponse(this->iSocket, "353 " + channel + " = " + channel + " :" + _channel->second.getClientsList());
        this->_server->sendResponse(this->iSocket, "366 " + channel + " :End of /NAMES list");
    }
}
