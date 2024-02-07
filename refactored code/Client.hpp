#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <map>

# include "General.hpp"

class Channel;
class Server;

class Client
{
	private:
		int								iSocket;
		std::string                     sSocket;
		std::string 					_username;
		std::string						_oldUsername;
		std::string						_nickname;
		std::string			            _oldNickname;
		std::string						_password;
		Channel*						_channel;
		Server*							_server;
	public:
		Client(struct newConnection& newClient);
		~Client();
		void commandHandler(struct request& request);
		void changeNickname(const std::string& newNickname);
		void changeUsername(const std::string& newUsername);
		//channel commands
		void join(const std::string& channel, const std::string& password);
		void leave();
		void kick(const std::string& nickname);
		void invite(const std::string& nickname);
		void topic(const std::string& topic);
		//mode commands
		void modeHandler(const std::string& modeFlag, const std::string& nickname);
		void modeI();
		void modeT();
		void modeK();
		void modeO(const std::string& nickname);
		void modeL(const std::string& limit);
		//message commands
		void sendToAll(const std::string& message);
		void sendToUser(const std::string& nickname, const std::string& message);
		//accessors
		int getISocket() const;
		std::string getSSocket() const;
		std::string getUsername() const;
		std::string getOldUsername() const;
		std::string getNickname() const;
		std::string getOldNickname() const;
		std::string getPassword() const;
		void setServer(Server* server);
};


#endif
