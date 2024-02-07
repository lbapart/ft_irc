#ifndef GENERAL_HPP
# define GENERAL_HPP

# define ERROR 1
# define SUCCESS 0

#include <string>

struct newConnection
{
    int iSocket;
    std::string sSocket;
    std::string _userName;
    std::string _nickName;
    std::string _password;
};


struct request
{
    std::string command; //stores commands like join, mode, leave, etc.
    std::string modeFlag; //stores mode flags like -i, -t, -k, -o, -l
    std::string requestFd; //stores the fd of the client that sent the request
    std::string requestChannel; //stores the channel where the request was made
    std::string argument; //stores the arguments like name of the channel, nickname, etc.
}

#endif
