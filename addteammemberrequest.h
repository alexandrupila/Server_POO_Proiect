#ifndef ADDTEAMMEMBERREQUEST_H
#define ADDTEAMMEMBERREQUEST_H

#include "irequest.h"

class AddTeamMemberRequest : public IRequest
{
public:
    AddTeamMemberRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // ADDTEAMMEMBERREQUEST_H
