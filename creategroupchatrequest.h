#ifndef CREATEGROUPCHATREQUEST_H
#define CREATEGROUPCHATREQUEST_H

#include "irequest.h"

class CreateGroupChatRequest : public IRequest
{
public:
    CreateGroupChatRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CREATEGROUPCHATREQUEST_H
