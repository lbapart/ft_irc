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
		Channel*						_channel;
	public:
		Client(struct newConnection& newClient);
		~Client();
		void commandHandler(struct request& request);
		void changeNickname(const std::string& newNickname);
		void changeUsername(const std::string& newUsername);
		//channel commands
		void kick(const std::string& channel, const std::string& nickname);
		void invite(const std::string& nickname, const std::string& channel);
		void topic(const std::string& channel, const std::string& topic);
		void join(const std::string& channel, const std::string& password);
		void leave(const std::string& channel);
		//mode commands
		void modeHandler(const std::string& mode);
		void modeI(const std::string& user);
		void modeT(const std::string& mode);
		void modeK(const std::string& mode);
		void modeO(const std::string& mode);
		void modeL(const std::string& mode);
		//message commands
		void send(const std::string& channel, const std::string& message);
		//accessors
		int getSocket() const;
		std::string getNickname() const;
		std::string getPassword() const;
};


#endif
