#include "General.hpp"

static std::vector<std::string>	parseLines( const std::string &str, std::string sep ) {
	std::vector<std::string>	result;
	std::string					line;
	size_t						pos = 0;
	size_t						prev = 0;

	if (str.empty())
		throw int(42);

	while ((pos = str.find(sep, prev)) != std::string::npos) {
		line = str.substr(prev, pos - prev);
		if (!line.empty())
			result.push_back(line);
		prev = pos + sep.length();
	}
	line = str.substr(prev);
	if (!line.empty())
		result.push_back(line);
	return (result);
}

static void	validateNbrArgs( const std::string &line, const int &nbrArgs, bool isVarArgs = false ) {
	std::istringstream	iss(line);
	std::string			token;
	int					nbr = 0;

	while (std::getline(iss, token, ' '))
		nbr++;
	if (isVarArgs)
	{
		if (nbr < nbrArgs)
			throw std::runtime_error("Wrong number of arguments");
	}
	else
	{
		if (nbr != nbrArgs)
			throw std::runtime_error("Wrong number of arguments");
	}
}

static std::string	getArgByNbr( const std::string &line, const int &nbr ) {
	std::istringstream	iss(line);
	std::string			token;
	int					nbrArgs = 0;

	while (std::getline(iss, token, ' ')) {
		if (nbrArgs == nbr)
			return (token);
		nbrArgs++;
	}
	throw std::runtime_error("Wrong pattern");
}

static std::string	getOptionalArg( const std::string &line ) {
	if (line.find(":") != std::string::npos)
		return (line.substr(line.find(":") + 1));
	return ("");
}

static void	executeCommand( const int &fd, const std::string &line, Server *server ) {
	int				index = 0;
	std::string		commands[12] = {
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
    	"PART",
		"MODE"
	};


	for (index = 0; index < 11; index++)
		if (line.find(commands[index]) == 0)
			break;

	Client&	client = server->getClient(fd);
	switch (index) {
		case (0) :
			validateNbrArgs(line, 2);
			client.setPassword(getArgByNbr(line, 1));
			break;
		case (1) : // NICK
			validateNbrArgs(line, 2);
			client.setNickname(getArgByNbr(line, 1));
			break;
		case (2) : // Ping
			validateNbrArgs(line, 2);
			client.pong();
			break;
		case (3) : // USER
			validateNbrArgs(line, 2, true);
			client.setUsername(getArgByNbr(line, 1));
			break;
		case (4) : // TOPIC
			validateNbrArgs(line, 3, true);
			client.setTopic(getArgByNbr(line, 1), getOptionalArg(line));
			break;
		case (5) : // PRIVMSG
			validateNbrArgs(line, 3, true);
			client.sendPrvMsg(getArgByNbr(line, 1), getOptionalArg(line));
			break;
		case (6) : // JOIN
			try {
				validateNbrArgs(line, 2); // if no password is specified
				client.joinChannel(getArgByNbr(line, 1), "");
			} catch ( ... ) {
				validateNbrArgs(line, 3);
				client.joinChannel(getArgByNbr(line, 1), getArgByNbr(line, 2));
			}
			break;
		case (7) : // KICK
			validateNbrArgs(line, 4, true);
			client.kickUser(getArgByNbr(line, 1), getArgByNbr(line, 2), getOptionalArg(line));
			break;
		case (8) : // QUIT
			validateNbrArgs(line, 2, true);
			client.quit(getOptionalArg(line));
			break;
		case (9) : // INVITE
			validateNbrArgs(line, 3);
			client.inviteUser(getArgByNbr(line, 1), getArgByNbr(line, 2));
			break;
		case (10):   // LEAVE
			validateNbrArgs(line, 2, true);
			client.leaveChannel(getArgByNbr(line, 1));
			break;
		case (11):   // MODE
			{
				// validateNbrArgs(line, 4); to be implemented:)
				std::istringstream iss(line);
				std::string channelName, mode, arg;
				std::getline(iss, channelName, ' ');
				std::getline(iss, mode, ' ');
				std::getline(iss, channelName, ' ');
				std::getline(iss, arg, ' ');
				client.setMode(channelName, mode, arg); // to do later
			}
			break;
		default:
			break;
		}
}

void	Server::executeCommands( const int &fd, const std::string &line ) {
	std::vector<std::string> cmds;

	if (line.find("\r\n") != line.npos)
		cmds = parseLines(line, "\r\n");
	else
		cmds = parseLines(line, "\n");

	for (std::vector<std::string>::iterator it = cmds.begin(); it != cmds.end(); it++) {
		try {
			executeCommand(fd, *it, this);
		} catch ( const std::exception & ) {
			std::cerr << "[Unkown pattern]: " << *it << std::endl;
		}
	}

}
