#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <string>
# define SERVER_NAME "ft_irc"

class Response
{
	private:
		Response();
	public:
		~Response();
		// Successfull connection, takes nickname as argument (const std::string& nickname)
		static const std::string&	OKconnectionSuccess(const std::string& nickname);
		// Failed connection, takes nickname as argument (const std::string& nickname)
		static const std::string&	ERRconnectionFailed(const std::string& nickname);
		// Failed connection, invalid password, takes nickname as argument (const std::string& nickname)
		static const std::string&	ERRconnectionInvalidPassword(const std::string& nickname);

		// Successful join, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string&	OKjoinSuccess(const std::string& nickname, const std::string& channel);
		// Failed join, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string&	ERRjoinFailed(const std::string& nickname, const std::string& channel);

		// Successful set of nickname, takes old and new nickname as arguments (const std::string& oldNickname, const std::string& newNickname)
		static const std::string&	OKnickSetupSuccess(const std::string& oldNickname, const std::string& newNickname);
		// Failed set of nickname, takes old and new nickname as arguments (const std::string& oldNickname, const std::string& newNickname)
		static const std::string&	ERRnickSetupFailed(const std::string& oldNickname, const std::string& newNickname);

		// Successful leave, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string&	OKleaveSuccess(const std::string& nickname, const std::string& channel);
		// Failed leave, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string&	ERRleaveFailed(const std::string& nickname, const std::string& channel);


};

#endif