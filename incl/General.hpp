#ifndef GENERAL_HPP
# define GENERAL_HPP

# define ERROR 1
# define SUCCESS 0
# define ERR_CHANNELISFULL 471
# define ERR_BADCHANNELKEY 475
# define ERR_INVITEONLYCHAN 473

#include <string>
#include "Response.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Server;
class Channel;
class Client;

struct newConnection
{
    int _fd; //stores the socket of the client
    std::string _userName; //stores the username of the client
    std::string _nickName; //stores the nickname of the client
    std::string _password; //stores the password of the client
};


typedef enum e_command
{
    MODE,
    NICK,
    PART,
    USER,
    TOPIC,
    PRIVMSG,
    JOIN,
    KICK,
    QUIT,
    INVITE,
    LEAVE
} t_command;

typedef struct request
{
    std::string message; //stores the message sent by the client like private message or channel message to all
    t_command   command; //stores commands like join, mode, leave, etc.
    std::string modeFlag; //stores mode flags like -i, -t, -k, -o, -l
    std::string channelPassword; //stores the password of the channel
    int         requestFd; //stores the fd of the client that sent the request
    std::string requestChannel; //stores the channel where the request was made
    std::string argument; //stores the arguments like name of the channel, nickname
                        //or if the mode is -o set give a user the operator status, the nicname of the user to become operator
                        //or with -l flag, the limit of the channel
}   t_request;

int parseLines( t_request &req, const std::string &line, int fd );

#endif
