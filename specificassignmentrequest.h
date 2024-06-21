#ifndef SPECIFICASSIGNMENTREQUEST_H
#define SPECIFICASSIGNMENTREQUEST_H

#include "irequest.h"

class SpecificAssignmentRequest : public IRequest
{
public:
    SpecificAssignmentRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // SPECIFICASSIGNMENTREQUEST_H
