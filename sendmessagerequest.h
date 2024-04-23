#ifndef SENDMESSAGEREQUEST_H
#define SENDMESSAGEREQUEST_H

#include "irequest.h"

class SendMessageRequest : public IRequest
{
public:
    SendMessageRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // SENDMESSAGEREQUEST_H
