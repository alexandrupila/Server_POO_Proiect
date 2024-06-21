#ifndef SPECIFICTEAMREQUEST_H
#define SPECIFICTEAMREQUEST_H

#include "irequest.h"

class SpecificTeamRequest : public IRequest
{
public:
    SpecificTeamRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // SPECIFICTEAMREQUEST_H
