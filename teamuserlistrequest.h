#ifndef TEAMUSERLISTREQUEST_H
#define TEAMUSERLISTREQUEST_H

#include "irequest.h"

class TeamUserListRequest : public IRequest
{
public:
    TeamUserListRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // TEAMUSERLISTREQUEST_H
