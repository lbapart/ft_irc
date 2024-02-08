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
		this->_server->sendResponse(this->iSocket, Response::ERRjoinFailed(this->_nickname, channel));
		return;
	}
	if (_channel->second.isPasswordProtected() && _channel->second.getPassword() != password)
	{
		this->_server->sendResponse(this->iSocket, Response::ERRjoinFailed(this->_nickname, channel));
		return;
	}
	else
	{
		for (std::set<int>::iterator it = _channel->second.getClients().begin(); it != _channel->second.getClients().end(); ++it)
		{
			this->_server->sendResponse(*it, Response::OKjoinSuccess(this->_nickname, channel));
		}
		_channel->second.addClient(*this);
		this->_channel = &_channel->second;
		this->_server->sendResponse(this->iSocket, Response::OKjoinSuccess(this->_nickname, channel));
	}
}
