#ifndef TEAMSREQUEST_H
#define TEAMSREQUEST_H

#include "irequest.h"

class TeamsRequest : public IRequest
{
public:
    TeamsRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;

};

#endif // TEAMSREQUEST_H
