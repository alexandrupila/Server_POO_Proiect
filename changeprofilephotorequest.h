#ifndef CHANGEPROFILEPHOTOREQUEST_H
#define CHANGEPROFILEPHOTOREQUEST_H

#include "irequest.h"

class ChangeProfilePhotoRequest : public IRequest
{
public:
    ChangeProfilePhotoRequest() {}
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CHANGEPROFILEPHOTOREQUEST_H
