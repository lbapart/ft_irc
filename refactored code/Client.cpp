#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

// Constructor && Destructor

Client::Client(struct newConnection& newClient)
{
	this->iSocket = newClient.iSocket;
	this->sSocket = newClient.sSocket;
	this->_username = newClient._userName;
	this->_oldUsername = "";
	this->_nickname = newClient._nickName;
	this->_oldNickname = "";
	this->_password = newClient._password;
	this->_channel = NULL;
}

Client::~Client()
{
}

//////////////////////////////////////////////////////////////////////////////////////////

// Accessors

int Client::getISocket() const
{
	return this->iSocket;
}

std::string Client::getSSocket() const
{
	return this->sSocket;
}

std::string Client::getUsername() const
{
	return this->_username;
}

std::string Client::getOldUsername() const
{
	return this->_oldUsername;
}

std::string Client::getNickname() const
{
	return this->_nickname;
}

std::string Client::getOldNickname() const
{
	return this->_oldNickname;
}

std::string Client::getPassword() const
{
	return this->_password;
}

void Client::setServer(Server* server)
{
	this->_server = server;
}

//////////////////////////////////////////////////////////////////////////////////////////

// Command Handler

void Client::commandHandler(request & request)
{
	switch (request.command)
	{
		case (JOIN): join(request.argument, request.channelPassword);	break;
		case (LEAVE): leave();											break;
		case (MODE): modeHandler(request.modeFlag, request.argument);	break;
		case (KICK): kick(request.argument);							break;
		case (INVITE): invite(request.argument);						break;
		case (TOPIC): topic(request.argument);							break;
		case (NICK): changeNickname(request.argument);					break;
		case (USER): changeUsername(request.argument);					break;
		case (PRIVMSG): sendToUser(request.argument, request.message);	break;
		default: sendToAll(request.message);
	}
}
