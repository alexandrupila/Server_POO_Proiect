#ifndef ADMINLISTREQUEST_H
#define ADMINLISTREQUEST_H

#include "irequest.h"

class AdminListRequest : public IRequest
{
public:
    AdminListRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // ADMINLISTREQUEST_H
