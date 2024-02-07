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

	if (request.command == "JOIN")
	{
		join(request.argument, request.channelPassword);
		return;
	}
	else if (request.command == "LEAVE")
	{
		leave();
		return;
	}
	else if (request.command == "MODE")
	{
		modeHandler(request.modeFlag, request.argument);
		return;
	}
	else if (request.command == "KICK")
	{
		kick(request.argument);
		return;
	}
	else if (request.command == "INVITE")
	{
		invite(request.argument);
		return;
	}
	else if (request.command == "TOPIC")
	{
		topic(request.argument);
		return;
	}
	else if (request.command == "NICK")
	{
		changeNickname(request.argument);
		return;
	}
	else if (request.command == "USER")
	{
		changeUsername(request.argument);
		return;
	}
	else if (request.command == "PRIVMSG")
	{
		sendToUser(request.argument,request.message);
		return;
	}
	else if (request.command.empty() && !request.argument.empty() && this->_channel != NULL)
	{
		sendToAll(request.argument);
		return;
	}
}
