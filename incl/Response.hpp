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
		// Ping
		// Successful ping, takes nickname as argument (const std::string& nickname)
		static const std::string	OKpingSuccess(const std::string& nickname);
		// Failed ping, takes nickname as argument (const std::string& nickname)
		static const std::string	ERRpingFailed(const std::string& nickname);
		// Connection
		// Successfull connection, takes nickname as argument (const std::string& nickname)
		static const std::string	OKconnectionSuccess(const std::string& nickname);
		// Failed connection, takes nickname as argument (const std::string& nickname)
		static const std::string	ERRconnectionFailed(const std::string& nickname);
		// Failed connection, invalid password, takes nickname as argument (const std::string& nickname)
		static const std::string	ERRconnectionInvalidPassword(const std::string& nickname);

		// Join
		// Successful join, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKjoinSuccess(const std::string& nickname, const std::string& username, const std::string& channel);
		// Failed join, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRjoinFailed(const std::string& nickname, const std::string& channel, int error);

		// Nick
		// Successful set of nickname, takes old and new nickname as arguments (const std::string& oldNickname, const std::string& newNickname)
		static const std::string	OKnickSetupSuccess(const std::string& oldNickname, const std::string& newNickname, const std::string& username);
		// Failed set of nickname, takes old and new nickname as arguments (const std::string& oldNickname, const std::string& newNickname)
		static const std::string	ERRnickSetupFailed(const std::string& oldNickname, const std::string& newNickname);

		// Leave
		// Successful leave, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKleaveSuccess(const std::string& nickname, const std::string& username, const std::string& channel);
		// Failed leave, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRleaveFailed(const std::string& nickname, const std::string& channel);

		// Messages
		// Successful message, takes nickname, channel and message as arguments (const std::string& nickname, const std::string& message)
		static const std::string	OKmessageSuccess(const std::string& nickname, const std::string& username, const std::string& channel, const std::string& message);
		// Failed message, takes nickname, channel and message as arguments (const std::string& nickname, const std::string& message)
		static const std::string	ERRmessageFailed(const std::string& nickname, const std::string& channel);
		// Successful private message, takes nicknames (sender, receiver) and message as arguments (const std::string& sender, const std::string& receiver  ,const std::string& message)
		static const std::string	OKprivateMessageSuccess(const std::string& sender, const std::string& receiver, const std::string& message);
		// Failed private message, takes nicknames (sender, receiver) and message as arguments (const std::string& sender, const std::string& receiver  ,const std::string& message)
		static const std::string	ERRprivateMessageFailed(const std::string& sender, const std::string& receiver);

		// Invite
		// Successful invite, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKinviteSuccess(const std::string& nickname, const std::string& username, const std::string& invitedUsername, const std::string& channel);

		// Failed invite, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRinviteFailed(const std::string& nickname, const std::string& channel);

		// Kick
		// Successful kick, takes nickname, username, kickedUsername, channel and reason as arguments (const std::string& nickname, const std::string& username, const std::string& kickedUsername, const std::string& channel, const std::string& reason)
		static const std::string	OKkickSuccess(const std::string& nickname, const std::string& username, const std::string& kickedUsername, const std::string& channel, const std::string& reason);
		// Failed kick, takes nickname, channel and username as arguments (const std::string& nickname, const std::string& channel, const std::string& username)
		static const std::string	ERRkickFailed(const std::string& nickname, const std::string& command, int error);

		// Set / view channel topic
		// Successful set channel topic, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKsetChannelTopicSuccess(const std::string& nickname, const std::string& channel, const std::string& topic);
		// Failed set channel topic, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRsetChannelTopicFailed(const std::string& nickname, const std::string& channel);
		// Successful view channel topic, takes nickname, channel and topic as arguments (const std::string& nickname, const std::string& channel, const std::string& topic)
		static const std::string	OKviewChannelTopicSuccess(const std::string& nickname, const std::string& channel, const std::string& topic);
		// Failed view channel topic, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRviewChannelTopicFailed(const std::string& nickname, const std::string& channel);

		// Set / unset channel password
		// Successful set channel password, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKsetChannelPasswordSuccess(const std::string& nickname, const std::string& channel);
		// Failed set channel password, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRsetChannelPasswordFailed(const std::string& nickname, const std::string& channel);
		// Successful unset channel password, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKunsetChannelPasswordSuccess(const std::string& nickname, const std::string& channel);
		// Failed unset channel password, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRunsetChannelPasswordFailed(const std::string& nickname, const std::string& channel);

		// Set / unset invite only mode
		// Successful set invite only mode, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKsetInvateOnlyModeSuccess(const std::string& nickname, const std::string& channel);
		// Failed set invite only mode, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRsetInvateOnlyModeFailed(const std::string& nickname, const std::string& channel);
		// Successful unset invite only mode, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKunsetInvateOnlyModeSuccess(const std::string& nickname, const std::string& channel);
		// Failed unset invite only mode, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRunsetInvateOnlyModeFailed(const std::string& nickname, const std::string& channel);

		// Successful set topic restricted, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKsetTopicRestrictedSuccess(const std::string& nickname, const std::string& channel);
		// Failed set topic restricted, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRsetTopicRestrictedFailed(const std::string& nickname, const std::string& channel);
		// Successful unset topic restricted, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKunsetTopicRestrictedSuccess(const std::string& nickname, const std::string& channel);
		// Failed unset topic restricted, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRunsetTopicRestrictedFailed(const std::string& nickname, const std::string& channel);

		// Give / take operator status
		// Successful give operator status, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKgiveOperatorStatusSuccess(const std::string& nickname, const std::string& channel);
		// Failed give operator status, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRgiveOperatorStatusFailed(const std::string& nickname, const std::string& channel);
		// Successful take operator status, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	OKtakeOperatorStatusSuccess(const std::string& nickname, const std::string& channel);
		// Failed take operator status, takes nickname and channel as arguments (const std::string& nickname, const std::string& channel)
		static const std::string	ERRtakeOperatorStatusFailed(const std::string& nickname, const std::string& channel);

		// Quit
		// Successful quit, takes nickname and reason as arguments (const std::string& nickname, const std::string& reason)
		static const std::string	OKquitSuccess(const std::string& nickname, const std::string& username, const std::string& reason);


		// Beautiful error messages
		static const std::string	ERRmsgToChannel(const std::string& nickname, const std::string& command, const std::string& message);
		static const std::string	ERRmsgToUser(const std::string& nickname, const std::string& command, const std::string& message);
		// Unkown command
		// Failed unknown command, takes nickname and command as arguments (const std::string& nickname, const std::string& command)
		static const std::string	ERRunknownCommand(const std::string& nickname, const std::string& command);
};

#endif