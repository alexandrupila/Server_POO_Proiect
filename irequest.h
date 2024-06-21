#ifndef IREQUEST_H
#define IREQUEST_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include "queryhandler.h"
#include "datatransferhandler.h"
#include "okresponse.h"
#include "errorresponse.h"

class IRequest
{
public:
    IRequest();
    virtual void processRequest(QJsonObject request,QTcpSocket* clientSocket)=0;
};

#endif // IREQUEST_H
