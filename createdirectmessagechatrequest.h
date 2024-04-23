#ifndef CREATEDIRECTMESSAGECHATREQUEST_H
#define CREATEDIRECTMESSAGECHATREQUEST_H

#include "irequest.h"

class CreateDirectMessageChatRequest : public IRequest
{
public:
    CreateDirectMessageChatRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CREATEDIRECTMESSAGECHATREQUEST_H
