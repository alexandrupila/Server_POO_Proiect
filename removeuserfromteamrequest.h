#ifndef REMOVEUSERFROMTEAMREQUEST_H
#define REMOVEUSERFROMTEAMREQUEST_H

#include "irequest.h"

class RemoveUserFromTeamRequest : public IRequest
{
public:
    RemoveUserFromTeamRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // REMOVEUSERFROMTEAMREQUEST_H
