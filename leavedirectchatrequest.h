#ifndef LEAVEDIRECTCHATREQUEST_H
#define LEAVEDIRECTCHATREQUEST_H

#include "irequest.h"

class LeaveDirectChatRequest : public IRequest
{
public:
    LeaveDirectChatRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // LEAVEDIRECTCHATREQUEST_H
