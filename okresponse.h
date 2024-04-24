#ifndef OKRESPONSE_H
#define OKRESPONSE_H

#include "aresponse.h"

class OkResponse : public AResponse
{
protected:
    QString reason;
public:
    OkResponse(QString reason="default");
    void sendResponse(QTcpSocket* clientsocket) override;
};

#endif // OKRESPONSE_H
