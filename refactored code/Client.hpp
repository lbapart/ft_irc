#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <map>

# include "General.hpp"

class Channel;

class Client
{
	private:
		int								_socket;
		std::string 					_username;
		std::string						_nickname;
		std::string						_password;
	public:
		Client(struct newConnection& newClient);
		~Client();
		void join(const std::string& channel, const std::string& password);
		void leave(const std::string& channel);
		void send(const std::string& channel, const std::string& message);
		//accessors
		int getSocket() const;
		std::string getNickname() const;
		std::string getPassword() const;
};


#endif
