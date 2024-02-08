
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


int	parseLine( t_request &req, const std::string &line, int fd ) {
	if (line.empty())
		throw std::invalid_argument("Empty line");

	(void)(req);
	fd++;

	std::vector<std::string>	words = splitRN(line);
	for (size_t i = 0; i < words.size(); i++) {
		std::cout << "Line[" << i << "] " << words[i] << std::endl;
	}
	return (1);
}