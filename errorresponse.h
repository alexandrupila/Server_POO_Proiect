#ifndef ERRORRESPONSE_H
#define ERRORRESPONSE_H

#include "aresponse.h"

class ErrorResponse : public AResponse
{
protected:
    QString reason;
public:
    ErrorResponse(QString reason="default");
    void sendResponse(QTcpSocket* clientsocket) override;
};

#endif // ERRORRESPONSE_H
