#ifndef SENDMESSAGECHANNELREQUEST_H
#define SENDMESSAGECHANNELREQUEST_H

#include "irequest.h"

class SendMessageChannelRequest : public IRequest
{
public:
    SendMessageChannelRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // SENDMESSAGECHANNELREQUEST_H
