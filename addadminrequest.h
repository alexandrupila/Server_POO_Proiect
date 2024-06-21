#ifndef ADDADMINREQUEST_H
#define ADDADMINREQUEST_H

#include "irequest.h"

class AddAdminRequest : public IRequest
{
public:
    AddAdminRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // ADDADMINREQUEST_H
