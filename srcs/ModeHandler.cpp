#include "General.hpp"


void Client::modeHandler(const std::string & modeFlag, const std::string & arguments)
{
    if (this->_channel == NULL)
    {
        this->_server->sendResponse(this->iSocket, Response::ERRsetModeFailed(this->getNickname(), ""));
        return;
    }
    if (this->_channel->getOperators().find(this->iSocket) == this->_channel->getOperators().end())
    {
        this->_server->sendResponse(this->iSocket, Response::ERRsetModeFailed(this->getNickname(), this->_channel->getName()));
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
	int fd = this->_server->getClientIdByNickname(nickname);
    if (this->_channel == NULL || this->_channel->getClients().count(fd) == 0)
    {
        this->_server->sendResponse(this->iSocket, Response::ERRsetModeFailed(this->getNickname(), ""));
        return;
    }
    if (this->_channel->getOperators().count(fd) == 0)
        this->_channel->addOperator(_server->getClient(fd));
    else
        this->_channel->removeOperator(_server->getClient(fd));
}
