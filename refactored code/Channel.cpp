#include "Channel.hpp"
#include "Client.hpp"


Channel::Channel(std::string name, const std::string& password)
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
}

Channel::~Channel()
{
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

std::string Channel::getName() const
{
	return this->_name;
}

std::string Channel::getPassword() const
{
	return this->_password;
}

std::map<std::string, Client>& Channel::getClients()
{
	return this->_clients;
}

std::map<std::string, Client>& Channel::getOperators()
{
	return this->_operators;
}

std::string Channel::getTopic() const
{
	return this->_topic;
}


std::string Channel::getClientsList()
{
	std::string list;
	std::map<std::string, Client>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		list += it->first + " ";
		it++;
	}
	return list;
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
	this->_clients[client.getNickname()] = client;
}

void Channel::removeClient(Client & client)
{
	this->_clients.erase(client.getNickname());
}

void Channel::addOperator(Client & client)
{
	this->_operators[client.getNickname()] = client;
}

void Channel::removeOperator(Client & client)
{
	this->_operators.erase(client.getNickname());
}

void Channel::setLimit(int limit)
{
	this->_userLimit = limit;
}
