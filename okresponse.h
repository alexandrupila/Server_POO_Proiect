#ifndef OKRESPONSE_H
#define OKRESPONSE_H

#include "aresponse.h"
#include "QJsonObject"

class OkResponse : public AResponse
{
protected:
    QString reason;
    QJsonObject object;
public:
    OkResponse(QString reason="default");
    OkResponse(QJsonObject object, QString reason="default");
    void sendResponse(QTcpSocket* clientsocket) override;
};

#endif // OKRESPONSE_H
