#ifndef CREATECHANNELREQUEST_H
#define CREATECHANNELREQUEST_H

#include "irequest.h"

class CreateChannelRequest : public IRequest
{
public:
    CreateChannelRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CREATECHANNELREQUEST_H
