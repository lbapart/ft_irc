#include "Channel.hpp"
#include "Client.hpp"


Channel::Channel(std::string name, const std::string& password)
{
	this->_name = name;
	this->_password = password;
}

Channel::~Channel()
{
}
