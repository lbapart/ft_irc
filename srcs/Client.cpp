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

void 		Client::setUsername(const std::string& username)
{
	this->_username = this->_server->getAvailableUsername(username);
	this->_isUsernameSet = true;
	this->checkAndSetAuthentificated();
}

void Client::setNickname(const std::string& nickname)
{
	// if nickname not set, set it
	if (!this->_isNicknameSet)
	{
		this->_nickname = this->_server->getAvailableNickname(nickname);
		this->_isNicknameSet = true;
		this->checkAndSetAuthentificated();
		return ;
	}
	// otherwise, change it
	std::string newNickname = std::string(nickname.begin(), nickname.end());
	if (this->_server->existByNickname(newNickname))
		this->_server->sendResponse(this->_fd, Response::ERRnickSetupFailed(this->_nickname, newNickname));
	else
	{
		for (std::vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
		{
			(*it)->postMessageInChannel(this->_nickname, this->_username, "has changed his nickname to " + newNickname);
		}
		for (std::map<int, Client>::iterator it = this->_server->getClients().begin(); it != this->_server->getClients().end(); it++)
		{
			this->_server->sendResponse(it->second.getFd(), Response::OKnickSetupSuccess(this->_nickname, newNickname, this->_username));
		}
		this->_nickname = newNickname;
	}
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

void		Client::pong( void )
{
	this->_server->sendResponse(this->_fd, "PONG :localhost\r\n");
}

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
	if (channel == NULL)
	{
		this->_channels.push_back(this->_server->addChannel(channelName, password, this->_fd));
		this->_server->sendResponse(this->_fd, Response::OKjoinSuccess(this->_nickname, this->_username, channelName));
		this->_channels.back()->postMessageInChannel(this->_nickname, this->_username, "has joined the channel");
		return ;
	}
	// if channel exists
	int code = channel->addClient(this->_fd, password);
	if (code != SUCCESS)
	{
		this->_server->sendResponse(this->_fd, Response::ERRjoinFailed(this->_nickname, channelName, code));
		return ;
	}
	this->_channels.push_back(channel);
	this->_server->sendResponse(this->_fd, Response::OKjoinSuccess(this->_nickname, this->_username, channelName));
	this->_channels.back()->postMessageInChannel(this->_nickname, this->_username, "has joined the channel");
}

void		Client::leaveChannel(const std::string& channelName)
{
	// check if user is in this channel
	for (std::vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		// if user is in this channel remove him from it
		if ((*it)->getName() == channelName)
		{
			(*it)->removeClient(this->_fd);
			(*it)->removeOperator(this->_fd);
			(*it)->removeInvite(this->_fd);
			this->_server->sendResponse(this->_fd, Response::OKleaveSuccess(this->_nickname, this->_username, channelName));
			(*it)->postMessageInChannel(this->_nickname, this->_username ,"has left the channel");
			std::cout << '\'' << this->_nickname << '\'' << " has left the channel" << std::endl;
			this->_channels.erase(it);
			return ;
		}
	}
	this->_server->sendResponse(this->_fd, Response::ERRleaveFailed(this->_nickname, channelName));
}