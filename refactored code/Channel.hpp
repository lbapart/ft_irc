#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <map>

# include "General.hpp"

class Client;

class Channel
{
	private:
		std::string							_name;
		std::string							_password;
		std::map<std::string, Client>		_clients;
		std::map<std::string, Client>		_operators;
	public:
		Channel(std::string name, const std::string& password);
		~Channel();
		void join(int client);
		void leave(int client);
		void send(int client, const std::string& message);
};


#endif
