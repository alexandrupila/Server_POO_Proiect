#ifndef CREATETEAMREQUEST_H
#define CREATETEAMREQUEST_H

#include "irequest.h"

class CreateTeamRequest : public IRequest
{
public:
    CreateTeamRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CREATETEAMREQUEST_H
