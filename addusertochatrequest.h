#ifndef ADDUSERTOCHATREQUEST_H
#define ADDUSERTOCHATREQUEST_H

#include "irequest.h"

class AddUserToChatRequest : public IRequest
{
public:
    AddUserToChatRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // ADDUSERTOCHATREQUEST_H
