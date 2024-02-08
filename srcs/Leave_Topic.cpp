#include "General.hpp"

void Client::leave()
{
	if (this->_channel == NULL)
	{
		this->_server->sendResponse(this->iSocket, Response::ERRleaveFailed(this->getNickname(), this->_channel->getName()));
		return;
	}
	this->_channel->removeClient(*this);
	this->_server->sendResponse(this->iSocket, Response::OKleaveSuccess(this->getNickname(), this->_channel->getName()));
	for (std::set<int>::iterator it = this->_channel->getClients().begin(); it != this->_channel->getClients().end(); ++it)
	{
		this->_server->sendResponse(*it, Response::UserLeftChannel(this->getNickname(), this->_channel->getName()));
	}
	this->_channel = NULL;
}

void Client::topic(const std::string& topic)
{
	if (this->_channel == NULL)
	{
		this->_server->sendResponse(this->iSocket, Response::ERRsetChannelTopic(this->getNickname(), this->_channel->getName()));
		return;
	}
	if (this->_channel->isTopicOperatorProtected() && this->_channel->getOperators().find(this->iSocket) == this->_channel->getOperators().end())
	{
		this->_server->sendResponse(this->iSocket, Response::ERRsetChannelTopic(this->getNickname(), this->_channel->getName()));
		return;
	}
	this->_channel->setTopic(topic);
	this->_server->sendResponse(this->iSocket, Response::OKsetChannelTopic(this->getNickname(), this->_channel->getName()));
	for (std::set<int>::iterator it = this->_channel->getClients().begin(); it != this->_channel->getClients().end(); ++it)
	{
		this->_server->sendResponse(*it, Response::TopicSet(this->getNickname(), this->_channel->getName(), topic));
	}
}
