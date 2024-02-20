#include "General.hpp"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		g_running = false;
}

static inline void	putIntro( void )
{
	std::cout << "───────────────────────────────────────────────────────────────────────────────" << std::endl;
	std::cout << "─██████████████─██████████████────██████████─████████████████───██████████████─" << std::endl;
	std::cout << "─██░░░░░░░░░░██─██░░░░░░░░░░██────██░░░░░░██─██░░░░░░░░░░░░██───██░░░░░░░░░░██─" << std::endl;
	std::cout << "─██░░██████████─██████░░██████────████░░████─██░░████████░░██───██░░██████████─" << std::endl;
	std::cout << "─██░░██─────────────██░░██──────────██░░██───██░░██────██░░██───██░░██─────────" << std::endl;
	std::cout << "─██░░██████████─────██░░██──────────██░░██───██░░████████░░██───██░░██─────────" << std::endl;
	std::cout << "─██░░░░░░░░░░██─────██░░██──────────██░░██───██░░░░░░░░░░░░██───██░░██─────────" << std::endl;
	std::cout << "─██░░██████████─────██░░██──────────██░░██───██░░██████░░████───██░░██─────────" << std::endl;
	std::cout << "─██░░██─────────────██░░██──────────██░░██───██░░██──██░░██─────██░░██─────────" << std::endl;
	std::cout << "─██░░██─────────────██░░██────────████░░████─██░░██──██░░██████─██░░██████████─" << std::endl;
	std::cout << "─██░░██─────────────██░░██────────██░░░░░░██─██░░██──██░░░░░░██─██░░░░░░░░░░██─" << std::endl;
	std::cout << "─██████─────────────██████────────██████████─██████──██████████─██████████████─" << std::endl;
	std::cout << "───────────────────────────────────────────────────────────────────────────────" << std::endl;
}

static bool	checkPort(const std::string& port)
{
	if (port.empty())
		return false;
	size_t len = port.length();
	if (len > 1 && port[0] == '0')
		return false;
	if (len > 5)
		return false;
	if (len == 5 && port.compare("65535") > 0)
		return false;
	for (std::string::const_iterator it = port.begin(); it != port.end(); ++it)
	{
		if (!std::isdigit(*it))
			return false;
	}
	return true;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password> !" << std::endl;
		return 1;
	}
	try
	{
		if (!checkPort(std::string(argv[1])))
			throw std::invalid_argument("Invalid port");
		if (std::string(argv[2]).empty())
			throw std::invalid_argument("Invalid password");
		std::stringstream port(argv[1]);
		ushort _port;
		port >> _port;
		if (port.fail())
			throw std::invalid_argument("Invalid port");
		Server server(_port, std::string(argv[2]));
		signal(SIGINT, signal_handler);
		putIntro();
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
