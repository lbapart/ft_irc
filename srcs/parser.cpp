
#include "../incl/General.hpp"
#include <algorithm>
#include <cstddef>

static std::vector<std::string>	splitRN( const std::string &str ) {
	std::vector<std::string>	result;
	size_t						pos = 0;
	size_t						prev = 0;

	while ((pos = str.find("\r\n", prev)) != std::string::npos) {
		result.push_back(str.substr(prev, pos - prev));
		prev = pos + 2;
	}
	// result.push_back(str.substr(prev));
	return result;
}

static void	executeCommand( const std::string &line ) {
	// std::string	commands[11] = {
	// 	"MODE",
    // 	"NICK",
    // 	"PART",
    // 	"USER",
    // 	"TOPIC",
    // 	"PRIVMSG",
    // 	"JOIN",
    // 	"KICK",
    // 	"QUIT",
    // 	"INVITE",
    // 	"LEAVE"
	// };
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
		case 0:
			// PASS
			break;
		case 1:
			// NICK
			break;
		case 2:
			// PART
			break;
		case 3:
			// USER
			break;
		case 4:
			// TOPIC
			break;
		case 5:
			// PRIVMSG
			break;
		case 6:
			// JOIN
			break;
		case 7:
			// KICK
			break;
		case 8:
			// QUIT
			break;
		case 9:
			// INVITE
			break;
		case 10:
			// LEAVE
			break;
		default:
			break;
		}
}

int	parseLines( t_request &req, const std::string &line, int fd ) {
	if (line.empty())
		throw std::invalid_argument("Empty line");

	req.requestFd = fd;

	std::vector<std::string>	cmds = splitRN(line);
	for (size_t i = 0; i < cmds.size(); i++) {
		executeCommand(cmds[i]);
	}
	return (1);
}