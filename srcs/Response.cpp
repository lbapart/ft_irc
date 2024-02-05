#include "Response.hpp"

Response::Response()
{
	;
}

Response::~Response()
{
	;
}

const std::string&	Response::OKconnectionSuccess(const std::string& nickname)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 001 " + nickname + " :Welcome to the Internet Relay Network " + nickname + "!" + SERVER_NAME + "@localhost\r\n";
	return response.c_str();
}

const std::string&	Response::ERRconnectionFailed(const std::string& nickname)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 464 " + nickname + " :Nickname is already in use\r\n";
	return response.c_str();
}

const std::string&	Response::OKjoinSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + nickname + "!" + std::string(SERVER_NAME) + "@localhost JOIN " + channel + "\r\n";
	return response.c_str();
}

const std::string&	Response::ERRjoinFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 474 " + nickname + " " + channel + " :No such channel\r\n";
	return response.c_str();
}

const std::string& Response::OKnickSetupSuccess(const std::string& oldNickname, const std::string& newNickname)
{
	std::string response = ":" + oldNickname + "!" + std::string(SERVER_NAME) + "@localhost NICK :" + newNickname + "\r\n";
    return response.c_str();
}

const std::string& Response::ERRnickSetupFailed(const std::string& oldNickname, const std::string& newNickname)
{
	std::string response = ":" + oldNickname + "!" + std::string(SERVER_NAME) + " 433 * " + newNickname + " :Nickname is already in use\r\n";
    return response.c_str();
}