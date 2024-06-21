#ifndef DELETETEAMREQUEST_H
#define DELETETEAMREQUEST_H

#include "irequest.h"

class DeleteTeamRequest : public IRequest
{
public:
    DeleteTeamRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // DELETETEAMREQUEST_H
