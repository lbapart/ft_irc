#include "Client.hpp"
#include "Channel.hpp"


Client::Client(int socket, const std::string& password)
{
	this->_socket = socket;
	this->_password = password;
}

Client::~Client()
{
}
