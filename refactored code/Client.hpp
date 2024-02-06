#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <map>

# include "Defines.hpp"

class Channel;

class Client
{
	private:
		int								_socket;
		std::string						_nickname;
		std::string						_password;
		std::map<std::string, Channel> 	_channels;
	public:
		Client(int socket, const std::string& password);
		~Client();
		void join(const std::string& channel, const std::string& password);
		void leave(const std::string& channel);
		void send(const std::string& channel, const std::string& message);
};


#endif
