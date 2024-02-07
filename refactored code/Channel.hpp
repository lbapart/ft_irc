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
		std::string							_topic;
		int									_userLimit;
		bool 								_passwordProtected;
		bool 								_inviteOnly;
		bool								_topicOperatorProtected;
		std::map<std::string, Client>		_clients;
		std::map<std::string, Client>		_operators;
	public:
		Channel(std::string name, const std::string& password);
		~Channel();
		// Accessors
		bool isPasswordProtected() const;
		bool isInviteOnly() const;
		bool isTopicOperatorProtected() const;
		std::string getPassword() const;
		std::string getName() const;
		std::string getTopic() const;
		std::string getClientsList();
		int getUserLimit() const;
		std::map<std::string, Client>& getClients();
		std::map<std::string, Client>& getOperators();
		// Setters
		void setLimit(int limit);
		void setTopic(const std::string& topic);
		void setPassword(const std::string& password);
		void setPasswordProtected(bool passwordProtected);
		void setTopicOperatorProtected(bool topicOperatorProtected);
		void setInviteOnly(bool inviteOnly);
		void addClient(Client & client);
		void removeClient(Client & client);
		void addOperator(Client & client);
		void removeOperator(Client & client);
};


# endif
