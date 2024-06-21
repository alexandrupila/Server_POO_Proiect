#ifndef FILEREQUEST_H
#define FILEREQUEST_H

#include "irequest.h"

class FileRequest : public IRequest
{
public:
    FileRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // FILEREQUEST_H
