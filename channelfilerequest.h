#ifndef CHANNELFILEREQUEST_H
#define CHANNELFILEREQUEST_H

#include "irequest.h"

class ChannelFileRequest : public IRequest
{
public:
    ChannelFileRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CHANNELFILEREQUEST_H
