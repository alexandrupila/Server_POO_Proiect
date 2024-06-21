#ifndef CREATEASSIGNMENTREQUEST_H
#define CREATEASSIGNMENTREQUEST_H

#include "irequest.h"

class CreateAssignmentRequest : public IRequest
{
public:
    CreateAssignmentRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CREATEASSIGNMENTREQUEST_H
