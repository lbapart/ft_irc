#include "Response.hpp"

// connection
// join
// nick
// leave
// message
// private message
// invite
// kick
// set channel password
// view channel topic
// set channel topic

Response::Response()
{
	;
}

Response::~Response()
{
	;
}

const std::string	Response::OKpingSuccess(const std::string& nickname)
{
	std::string response = ":" + std::string(SERVER_NAME) + " PONG " + nickname + " :localhost\r\n";
	return response;
}

const std::string	Response::ERRpingFailed(const std::string& nickname)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 421 " + nickname + " :Unknown command\r\n";
	return response;
}

const std::string	Response::OKconnectionSuccess(const std::string& nickname)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 001 " + nickname + " :Welcome to the Internet Relay Network " + nickname + "!" + SERVER_NAME + "@localhost\r\n";
	return response;
}

const std::string	Response::ERRconnectionFailed(const std::string& nickname)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 464 " + nickname + " :Nickname is already in use\r\n";
	return response;
}

const std::string	Response::ERRconnectionInvalidPassword(const std::string& nickname)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 464 " + nickname + " :Invalid password toscho\r\n";
	return response;
}

const std::string	Response::OKjoinSuccess(const std::string& nickname, const std::string& username, const std::string& channel)
{
	std::string response = ":" + nickname + "!" + username + "@localhost JOIN :" + channel + "\r\n";
	return response;
}

const std::string	Response::ERRjoinFailed(const std::string& nickname, const std::string& channel, int error)
{
	std::string response = ":" + std::string(SERVER_NAME) + " " + std::to_string(error) + " " + nickname + " " + channel + " :Cannot join channel (+k)\r\n";
	return response;
}

const std::string	Response::OKnickSetupSuccess(const std::string& oldNickname, const std::string& newNickname, const std::string& username)
{
	std::string response = ":" + oldNickname + "!" + username + "@localhost NICK :" + newNickname + "\r\n";
	return response;
}

const std::string	Response::ERRnickSetupFailed(const std::string& oldNickname, const std::string& newNickname)
{
	std::string response = ":" + oldNickname + "!" + std::string(SERVER_NAME) + " 433 * " + newNickname + " :Nickname is already in use\r\n";
    return response;
}

const std::string	Response::OKleaveSuccess(const std::string& nickname, const std::string& username, const std::string& channel)
{
	std::string response = ":" + nickname + "!" + username + "@localhost PART " + channel  + "\r\n";
	return response;
}

const std::string	Response::ERRleaveFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 403 " + nickname + " " + channel + " :No such channel\r\n";
	return response;
}

const std::string	Response::OKmessageSuccess(const std::string& nickname, const std::string& username, const std::string& channel, const std::string& message)
{
	std::string response = ":" + nickname + "!" + username + "@localhost PRIVMSG " + channel + " :" + message + "\r\n";
	return response;
}

const std::string	Response::ERRmessageFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 404 " + nickname + " " + channel + " :Cannot send to channel\r\n";
	return response;
}

// не уверен, что это правильно
const std::string	Response::OKprivateMessageSuccess(const std::string& sender, const std::string& receiver, const std::string& message)
{
	std::string response = ":" + sender + "!" + std::string(SERVER_NAME) + "@localhost PRIVMSG " + receiver + " :" + message + "\r\n";
	return response;
}

const std::string	Response::ERRprivateMessageFailed(const std::string& sender, const std::string& receiver)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 401 " + sender + " " + receiver + " :No such nick/channel\r\n";
	return response;
}

const std::string	Response::OKinviteSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 341 " + nickname + " " + channel + " :Invited successfully\r\n";
	return response;
}

const std::string	Response::ERRinviteFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 442 " + nickname + " " + channel + " :Invitation failed\r\n";
	return response;
}

const std::string	Response::OKkickSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 441 " + nickname + " " + channel + " :Kicked successfully\r\n";
	return response;
}

const std::string	Response::ERRkickFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 443 " + nickname + " " + channel + " :Kick failed\r\n";
	return response;
}

const std::string	Response::OKsetChannelPasswordSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 381 " + nickname + " " + channel + " :Password set successfully\r\n";
	return response;
}

const std::string	Response::ERRsetChannelPasswordFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 482 " + nickname + " " + channel + " :Password set failed\r\n";
	return response;
}

const std::string	Response::OKunsetChannelPasswordSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 382 " + nickname + " " + channel + " :Password unset successfully\r\n";
	return response;
}

const std::string	Response::ERRunsetChannelPasswordFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 482 " + nickname + " " + channel + " :Password unset failed\r\n";
	return response;
}

const std::string	Response::OKviewChannelTopicSuccess(const std::string& nickname, const std::string& channel, const std::string& topic)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 332 " + nickname + " " + channel + " :" + topic + "\r\n";
	return response;
}

const std::string	Response::ERRviewChannelTopicFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 403 " + nickname + " " + channel + " :No such channel\r\n";
	return response;
}

const std::string	Response::OKsetChannelTopicSuccess(const std::string& nickname, const std::string& channel, const std::string& topic)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 332 " + nickname + " " + channel + " :" + topic + "\r\n";
	return response;
}

const std::string	Response::ERRsetChannelTopicFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 442 " + nickname + " " + channel + " :Topic set failed\r\n";
	return response;
}

const std::string	Response::OKsetInvateOnlyModeSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 324 " + nickname + " " + channel + " :Invite only mode set successfully\r\n";
	return response;
}

const std::string	Response::ERRsetInvateOnlyModeFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 484 " + nickname + " " + channel + " :Invite only mode set failed\r\n";
	return response;
}

const std::string	Response::OKunsetInvateOnlyModeSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 325 " + nickname + " " + channel + " :Invite only mode unset successfully\r\n";
	return response;
}

const std::string	Response::ERRunsetInvateOnlyModeFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 484 " + nickname + " " + channel + " :Invite only mode unset failed\r\n";
	return response;
}

const std::string	Response::OKsetTopicRestrictedSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 329 " + nickname + " " + channel + " :Topic restricted set successfully\r\n";
	return response;
}

const std::string	Response::ERRsetTopicRestrictedFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 484 " + nickname + " " + channel + " :Topic restricted set failed\r\n";
	return response;
}

const std::string	Response::OKunsetTopicRestrictedSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 331 " + nickname + " " + channel + " :Topic restricted unset successfully\r\n";
	return response;
}

const std::string	Response::ERRunsetTopicRestrictedFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 484 " + nickname + " " + channel + " :Topic restricted unset failed\r\n";
	return response;
}

const std::string	Response::OKgiveOperatorStatusSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 381 " + nickname + " " + channel + " :Operator status given successfully\r\n";
	return response;
}

const std::string	Response::ERRgiveOperatorStatusFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 482 " + nickname + " " + channel + " :Operator status given failed\r\n";
	return response;
}

const std::string	Response::OKtakeOperatorStatusSuccess(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 382 " + nickname + " " + channel + " :Operator status taken successfully\r\n";
	return response;
}

const std::string	Response::ERRtakeOperatorStatusFailed(const std::string& nickname, const std::string& channel)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 482 " + nickname + " " + channel + " :Operator status taken failed\r\n";
	return response;
}

const std::string	Response::ERRunknownCommand(const std::string& nickname, const std::string& command)
{
	std::string response = ":" + std::string(SERVER_NAME) + " 421 " + nickname + " " + command + " :Unknown command\r\n";
	return response;
}
