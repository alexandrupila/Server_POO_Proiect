#ifndef IREQUEST_H
#define IREQUEST_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include "datatransferhandler.h"

class IRequest
{
public:
    IRequest();
    virtual void processRequest(QJsonObject request,QTcpSocket* clientSocket)=0;
};

#endif // IREQUEST_H
