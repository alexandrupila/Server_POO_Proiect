#ifndef LOGINRESPONSE_H
#define LOGINRESPONSE_H

#include "aresponse.h"
#include "user.h"

class LoginResponse : public AResponse
{
public:
    LoginResponse();
    LoginResponse(IUser *u) {this->requested_user=u;}
    virtual void sendResponse(QTcpSocket* clientsocket) override;
protected:
    IUser* requested_user;
};

#endif // LOGINRESPONSE_H
