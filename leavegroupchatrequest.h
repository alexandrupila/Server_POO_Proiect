#ifndef LEAVEGROUPCHATREQUEST_H
#define LEAVEGROUPCHATREQUEST_H

#include "irequest.h"

class LeaveGroupChatRequest : public IRequest
{
public:
    LeaveGroupChatRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // LEAVEGROUPCHATREQUEST_H
