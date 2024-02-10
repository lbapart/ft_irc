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

#include <csignal>

extern bool g_running;

#endif
