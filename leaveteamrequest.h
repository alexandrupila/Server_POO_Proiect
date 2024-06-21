#ifndef LEAVETEAMREQUEST_H
#define LEAVETEAMREQUEST_H

#include "arequest.h"

class LeaveTeamRequest : public ARequest
{
public:
    LeaveTeamRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // LEAVETEAMREQUEST_H
