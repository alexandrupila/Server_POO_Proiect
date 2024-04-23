#ifndef UPDATEPROFILEREQUEST_H
#define UPDATEPROFILEREQUEST_H

#include "irequest.h"

class UpdateProfileRequest : public IRequest
{
public:
    UpdateProfileRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // UPDATEPROFILEREQUEST_H
