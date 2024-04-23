#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "irequest.h"

class LoginRequest : public IRequest
{
public:
    LoginRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // LOGINREQUEST_H
