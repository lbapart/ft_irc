#include "Client.hpp"
#include "Channel.hpp"

// Constructor && Destructor

Client::Client(struct newConnection& newClient)
{
	this->_socket = newClient.iSocket;
	this->_username = newClient._userName;
	this->_nickname = newClient._nickName;
	this->_password = newClient._password;
}

Client::~Client()
{
}

// Methods

int Client::getSocket() const
{
	return this->_socket;
}

std::string Client::getNickname() const
{
	return this->_nickname;
}

std::string Client::getPassword() const
{
	return this->_password;
}
