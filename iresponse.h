#ifndef IRESPONSE_H
#define IRESPONSE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>

class IResponse
{
public:
    IResponse();
    virtual void sendResponse(QTcpSocket* clientsocket)=0;
};

#endif // IRESPONSE_H
