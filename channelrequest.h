#ifndef CHANNELREQUEST_H
#define CHANNELREQUEST_H

#include "irequest.h"

class ChannelRequest : public IRequest
{
public:
    ChannelRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CHANNELREQUEST_H
