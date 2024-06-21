#ifndef DELETEGROUPREQUEST_H
#define DELETEGROUPREQUEST_H

#include "irequest.h"

class DeleteGroupRequest : public IRequest
{
public:
    DeleteGroupRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // DELETEGROUPREQUEST_H
