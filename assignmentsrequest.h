#ifndef ASSIGNMENTSREQUEST_H
#define ASSIGNMENTSREQUEST_H

#include "irequest.h"

class AssignmentsRequest : public IRequest
{
public:
    AssignmentsRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // ASSIGNMENTSREQUEST_H
