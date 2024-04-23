#ifndef REGISTERREQUEST_H
#define REGISTERREQUEST_H

#include <QObject>
#include "irequest.h"
#include "user.h"
class RegisterRequest : public IRequest
{
public:
    RegisterRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // REGISTERREQUEST_H
