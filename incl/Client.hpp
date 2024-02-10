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

		void			setUsername(std::string username);
		void			setNickname(std::string nickname);
		void			setPassword(const std::string& password);

		//methods
		void			pong( void );
		void			joinChannel(const std::string& channelName, const std::string& password);
		void			leaveChannel(const std::string& channelName);
		void			setTopic(const std::string& channelName, const std::string& topic);
		void			sendPrvMsg(const std::string& nickname, const std::string& message);
		void			kickUser(const std::string& channelName, const std::string& username, const std::string& reason);

		// int				changeChannelTopic(const std::string& topic);
		// int				kickClientFromChannel(const std::string& nickname);
		// int 			inviteClientToChannel(const std::string& nickname);

};


#endif
