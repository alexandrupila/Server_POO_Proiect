#ifndef REMOVEUSERFROMCHATREQUEST_H
#define REMOVEUSERFROMCHATREQUEST_H

#include "irequest.h"

class RemoveUserFromChatRequest : public IRequest
{
public:
    RemoveUserFromChatRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // REMOVEUSERFROMCHATREQUEST_H
