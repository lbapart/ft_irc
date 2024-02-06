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

#endif
