#ifndef SPECIFICCHATREQUEST_H
#define SPECIFICCHATREQUEST_H

#include "irequest.h"

class SpecificChatRequest : public IRequest
{
public:
    SpecificChatRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // SPECIFICCHATREQUEST_H
