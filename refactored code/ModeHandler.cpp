#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"


void Client::modeHandler(const std::string & modeFlag, const std::string & arguments)
{
    if (this->_channel == NULL)
    {
        this->_server->sendResponse(this->iSocket, "442 :You're not in a channel");
        return;
    }
    if (this->_channel->getOperators().find(this->_nickname) == this->_channel->getOperators().end())
    {
        this->_server->sendResponse(this->iSocket, "482 " + this->_channel->getName() + " :You're not a channel operator");
        return;
    }
    if (modeFlag == "-o" || modeFlag == "-O")
    {
        this->modeO(arguments);
        return ;
    }
    else if (modeFlag == "-i" || modeFlag == "-I")
    {
        this->modeI();
        return ;
    }
    else if (modeFlag == "-t" || modeFlag == "-T")
    {
        this->modeT();
        return ;
    }
    else if (modeFlag == "-k" || modeFlag == "-K")
    {
        this->modeK();
        return ;
    }
    else if (modeFlag == "-l" || modeFlag == "-L")
    {
        this->modeL(arguments);
        return ;
    }
}

void Client::modeI()
{
    if(!this->_channel->isInviteOnly())
        this->_channel->setInviteOnly(true);
    else
        this->_channel->setInviteOnly(false);
}

void Client::modeT()
{
    if(!this->_channel->isTopicOperatorProtected())
        this->_channel->setTopicOperatorProtected(true);
    else
        this->_channel->setTopicOperatorProtected(false);
}

void Client::modeK()
{
    if(!this->_channel->isPasswordProtected())
        this->_channel->setPasswordProtected(true);
    else
    {
        this->_channel->setPasswordProtected(false);
    }
}

void Client::modeL(const std::string& limit)
{
    std::stringstream ss(limit);
    int limitInt;
    ss >> limitInt;
    this->_channel->setLimit(limitInt);
}

void Client::modeO(const std::string& nickname)
{
    std::map<std::string, Client>::iterator _client = this->_channel->getClients().find(nickname);
    if (_client == this->_channel->getClients().end())
    {
        this->_server->sendResponse(this->iSocket, "441 " + nickname + " :They aren't on that channel");
        return;
    }
    if(this->_channel->getOperators().find(nickname) == this->_channel->getOperators().end())
        this->_channel->addOperator(_client->second);
    else
        this->_channel->removeOperator(_client->second);
}
