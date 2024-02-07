#include "General.hpp"

void Client::changeNickname(const std::string& newNickname)
{
    this->_oldNickname = this->_nickname;
    this->_nickname = newNickname;
}

void Client::changeUsername(const std::string& newUsername)
{
    this->_oldUsername = this->_username;
    this->_username = newUsername;
}
