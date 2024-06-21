#ifndef CHATUSERLISTREQUEST_H
#define CHATUSERLISTREQUEST_H

#include "irequest.h"

class ChatUserListRequest : public IRequest
{
public:
    ChatUserListRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CHATUSERLISTREQUEST_H
