#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
#include <regex>
# include <string>
# include <vector>

# include "General.hpp"

class Server;
class Channel;

class Client
{
	private:
		void							checkAndSetAuthentificated();
		int								_fd;
		std::string 					_username;
		std::string						_nickname;
		std::string						_password;
		bool							_isAuthentificated;
		bool							_isPasswordSet;
		bool							_isUsernameSet;
		bool							_isNicknameSet;
		std::vector<Channel *>			_channels;
		Server*							_server;
	public:
		Client();
		Client(int fd, Server *serv);
		~Client();
		//accessors
		int				getFd() const;
		std::string		getUsername() const;
		std::string		getNickname() const;
		std::string		getPassword() const;

		void			setUsername(const std::string& username);
		void			setNickname(const std::string& nickname);
		void			setPassword(const std::string& password);

		//methods
		void			pong( void );
		void			joinChannel(const std::string& channelName, const std::string& password);
		void			leaveChannel(const std::string& channelName);
		// int				changeChannelTopic(const std::string& topic);
		// int				kickClientFromChannel(const std::string& nickname);
		// int 			inviteClientToChannel(const std::string& nickname);

};


#endif
