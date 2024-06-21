#ifndef EMPTYREQUEST_H
#define EMPTYREQUEST_H

#include "irequest.h"

class EmptyRequest : public IRequest
{
public:
    EmptyRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // EMPTYREQUEST_H
