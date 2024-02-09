#include "Client.hpp"
#include "Server.hpp"

// Constructor && Destructor

Client::Client() {}

Client::Client(int fd, Server *serv)
{
	this->_fd = fd;
	this->_isAuthentificated = false;
	this->_isPasswordSet = false;
	this->_isUsernameSet = false;
	this->_isNicknameSet = false;
	this->_server = serv;
}

Client::~Client() {}

//////////////////////////////////////////////////////////////////////////////////////////

// Accessors

int Client::getFd() const
{
	return this->_fd;
}

std::string Client::getUsername() const
{
	return this->_username;
}

std::string Client::getNickname() const
{
	return this->_nickname;
}

std::string Client::getPassword() const
{
	return this->_password;
}

void Client::setUsername(const std::string& username)
{
	this->_username = username;
	this->_isUsernameSet = true;
	this->checkAndSetAuthentificated();
}

void Client::setNickname(const std::string& nickname)
{
	this->_nickname = nickname;
	this->_isNicknameSet = true;
	this->checkAndSetAuthentificated();
}

void Client::setPassword(const std::string& password)
{
	this->_password = password;
	this->_isPasswordSet = true;
	this->checkAndSetAuthentificated();
}

//////////////////////////////////////////////////////////////////////////////////////////
// Command Handler

void		Client::checkAndSetAuthentificated()
{
	std::cout << "isPasswordSet: " << this->_isPasswordSet << std::endl;
	std::cout << "isUsernameSet: " << this->_isUsernameSet << std::endl;
	std::cout << "isNicknameSet: " << this->_isNicknameSet << std::endl;
	if (!(this->_isPasswordSet && this->_isUsernameSet && this->_isNicknameSet))
		return ;
	std::cout << "fd: " << this->_fd << std::endl;
	if (this->_password == this->_server->getPassword())
	{
		this->_isAuthentificated = true;
		std::cout << "If you see this, it means that the password is correct" << std::endl;
		this->_server->sendResponse(this->_fd, Response::OKconnectionSuccess(this->_nickname));
	}
	else
	{
		std::cout << "If you see this, it means that the password is incorrect" << std::endl;
		this->_server->sendResponse(this->_fd, Response::ERRconnectionInvalidPassword(this->_nickname));
		this->_isAuthentificated = false;
	}
}

// methods

void		Client::joinChannel(const std::string& channelName, const std::string& password)
{
	// check if user is already in this channel
	if (this->_channels.size() > 0)
	{
		for (std::vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
		{
			if ((*it)->getName() == channelName)
			{
				this->_channels.erase(it);
				this->_channels.push_back(this->_server->getChannel(channelName));
				return ; // TODO: maybe we need to send a response to the client
			}
		}
	}

	Channel *channel = this->_server->getChannel(channelName);
	// if channel does not exist, create it
	// TODO : on join success, maybe we need to send a message to all of the clients in the channel
	if (channel == NULL)
	{
		this->_channels.push_back(this->_server->addChannel(channelName, password, this->_fd));
		this->_server->sendResponse(this->_fd, Response::OKjoinSuccess(this->_nickname, channelName));
		this->_channels.back()->postMessageInChannel(this->_nickname, "has joined the channel");
		return ;
	}
	// if channel exists
	if (channel->addClient(this->_fd, password) == ERROR)
	{
		this->_server->sendResponse(this->_fd, Response::ERRjoinFailed(this->_nickname, channelName));
		return ;
	}
	this->_channels.push_back(channel);
	this->_server->sendResponse(this->_fd, Response::OKjoinSuccess(this->_nickname, channelName));
	this->_channels.back()->postMessageInChannel(this->_nickname, "has joined the channel");
}
