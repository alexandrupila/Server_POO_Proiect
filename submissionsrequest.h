#ifndef SUBMISSIONSREQUEST_H
#define SUBMISSIONSREQUEST_H

#include "irequest.h"

class SubmissionsRequest : public IRequest
{
public:
    SubmissionsRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;

};

#endif // SUBMISSIONSREQUEST_H
