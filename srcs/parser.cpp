
#include "../incl/General.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>

static std::vector<std::string>	splitRN( const std::string &str ) {
	std::vector<std::string>	result;
	size_t						pos = 0;
	size_t						prev = 0;

	while ((pos = str.find("\r\n", prev)) != std::string::npos) {
		result.push_back(str.substr(prev, pos - prev));
		prev = pos + 2;
	}
	return result;
}

static void	executeCommand( const std::string &line ) {
	int				index = 0;
	std::string		commands[11] = {
		"PASS",
    	"NICK",
    	"PART",
    	"USER",
    	"TOPIC",
    	"PRIVMSG",
    	"JOIN",
    	"KICK",
    	"QUIT",
    	"INVITE",
    	"LEAVE"
	};

	for (index = 0; index < 11; index++)
		if (line.find(commands[index]) != line.npos)
			break;

	switch (index) {
		case (0) : 
			break;
		case (1) : // NICK
			break;
		case (2) : // PART
			break;
		case (3) : // USER
			break;
		case (4) : // TOPIC
			break;
		case (5) : // PRIVMSG
			break;
		case (6) : // JOIN
			break;
		case (7) : // KICK
			break;
		case (8) : // QUIT
			break;
		case (9) : // INVITE
			break;
		case (10):   // LEAVE
			break;
		default:
			break;
		}
}

int	parseLines( const std::string &line ) {
	if (line.empty())
		throw std::invalid_argument("Empty line");

	std::vector<std::string>	cmds = splitRN(line);
	std::cout << "Number of commands: " << cmds.size() << std::endl;
	for (size_t i = 0; i < cmds.size(); i++) {
		std::cout << "Command: " << cmds[i] << std::endl;
		executeCommand(cmds[i]);
	}
	return (1);
}