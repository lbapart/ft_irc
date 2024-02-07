#include "Channel.hpp"
#include "Client.hpp"


Channel::Channel(const std::string& name, const std::string& password, Client& client)
{
	this->_name = name;
	this->_password = password;
	this->_inviteOnly = false;
	if (password != "")
		this->_passwordProtected = true;
	else
		this->_passwordProtected = false;
	this->_topic = "";
	this->_topicOperatorProtected = false;
	this->_userLimit = -1;
	this->_clients[client.getISocket()] = client;
	this->_operators[client.getISocket()] = client;
}

Channel::~Channel()
{
	_clients.clear();
	_operators.clear();
}

// Accessors

bool Channel::isInviteOnly() const
{
	return this->_inviteOnly;
}

bool Channel::isPasswordProtected() const
{
	return this->_passwordProtected;
}

bool Channel::isTopicOperatorProtected() const
{
	return this->_topicOperatorProtected;
}

const std::string& Channel::getName() const
{
	return this->_name;
}

const std::string& Channel::getPassword() const
{
	return this->_password;
}

std::map<int, Client>& Channel::getClients()
{
	return this->_clients;
}

std::map<int, Client>& Channel::getOperators()
{
	return this->_operators;
}

const std::string& Channel::getTopic() const
{
	return this->_topic;
}


const std::string& Channel::getClientsList()
{
	std::string list;

	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		list += it->second.getNickname() + " ";
	}
	//TODO: check if it works
	list.pop_back();
	return list;
}

int 				Channel::getUserLimit() const
{
	return this->_userLimit;
}

// Setters

void Channel::setPassword(const std::string& password)
{
	this->_password = password;
}

void Channel::setPasswordProtected(bool passwordProtected)
{
	this->_passwordProtected = passwordProtected;
}

void Channel::setTopic(const std::string& topic)
{
	this->_topic = topic;
}

void Channel::setTopicOperatorProtected(bool topicOperatorProtected)
{
	this->_topicOperatorProtected = topicOperatorProtected;
}

void Channel::setInviteOnly(bool inviteOnly)
{
	this->_inviteOnly = inviteOnly;
}

void Channel::addClient(Client & client)
{
	this->_clients[client.getISocket()] = client;
}

void Channel::removeClient(Client & client)
{
	this->_clients.erase(client.getISocket());
}

void Channel::addOperator(Client & client)
{
	this->_operators[client.getISocket()] = client;
}

void Channel::removeOperator(Client & client)
{
	this->_operators.erase(client.getISocket());
}

void Channel::setLimit(int limit)
{
	this->_userLimit = limit;
}
