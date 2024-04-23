#ifndef CHATSREQUEST_H
#define CHATSREQUEST_H

#include "irequest.h"

class ChatsRequest : public IRequest
{
public:
    ChatsRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CHATSREQUEST_H
