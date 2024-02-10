
#include "../incl/General.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sstream>

static std::vector<std::string>	parseLines( const std::string &str ) {
	std::vector<std::string>	result;
	size_t						pos = 0;
	size_t						prev = 0;

	if (str.empty())
		throw std::invalid_argument("Empty line");

	while ((pos = str.find("\r\n", prev)) != std::string::npos) {
		result.push_back(str.substr(prev, pos - prev));
		prev = pos + 2;
	}
	return (result);
}

static void	executeCommand( const int &fd, const std::string &line, Server *server ) {
	int				index = 0;
	std::string		commands[11] = {
		"PASS",
    	"NICK",
    	"PING",
    	"USER",
    	"TOPIC",
    	"PRIVMSG",
    	"JOIN",
    	"KICK",
    	"QUIT",
    	"INVITE",
    	"PART"
	};


	for (index = 0; index < 11; index++)
		if (line.find(commands[index]) != line.npos)
			break;

	Client&	client = server->getClient(fd);
	switch (index) {
		case (0) :
			client.setPassword(line.substr(5));
			break;
		case (1) : // NICK
			client.setNickname(line.substr(5));
			break;
		case (2) : // Ping
			client.pong();
			break;
		case (3) : // USER
			{
				std::istringstream iss(line);
				std::string token;
				std::getline(iss, token, ' ');
				std::getline(iss, token, ' ');
				client.setUsername(token);
			}
			break;
		case (4) : // TOPIC
			{
				std::istringstream iss(line);
				std::string channelName, topic;
				std::getline(iss, channelName, ' ');
				std::getline(iss, channelName, ' ');
				std::getline(iss, topic, ' ');
				topic.assign(topic.begin() + 1, topic.end());
				client.setTopic(channelName, topic);
			}
			break;
		case (5) : // PRIVMSG
			{
				std::istringstream iss(line);
				std::string username, message;
				std::getline(iss, username, ' ');
				std::getline(iss, username, ' ');
				message = line.substr(line.find(":") + 1);
				client.sendPrvMsg(username, message);
			}
			break;
		case (6) : // JOIN
			{
				std::istringstream iss(line);
				std::string channelName, password;
				std::getline(iss, channelName, ' ');
				std::getline(iss, channelName, ' ');
				std::getline(iss, password, ' ');
				client.joinChannel(channelName, password);
			}
			break;
		case (7) : // KICK
			{
				std::istringstream iss(line);
				std::string channelName, username, reason;
				std::getline(iss, channelName, ' ');
				std::getline(iss, channelName, ' ');
				std::getline(iss, username, ' ');
				reason = line.substr(line.find(":") + 1);
				client.kickUser(channelName, username, reason);
			}
			break;
		case (8) : // QUIT
			{
				std::string reason = line.substr(line.find(":") + 1);
				client.quit(reason);
			}
			break;
		case (9) : // INVITE
			{
				std::istringstream iss(line);
				std::string nickname, channelName;
				std::getline(iss, nickname, ' ');
				std::getline(iss, nickname, ' ');
				std::getline(iss, channelName, ' ');
				client.inviteUser(nickname, channelName);
			}
			break;
		case (10):   // LEAVE
			{
				std::istringstream iss(line);
				std::string channelName;
				std::getline(iss, channelName, ' ');
				std::getline(iss, channelName, ' ');
				client.leaveChannel(channelName);
			}
			break;
		default:
			break;
		}
}

void	Server::executeCommands( const int &fd, const std::string &line ) {
	std::vector<std::string> cmds = parseLines(line);

	for (std::vector<std::string>::iterator it = cmds.begin(); it != cmds.end(); it++) {
		executeCommand(fd, *it, this);
	}

}
