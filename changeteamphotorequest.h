#ifndef CHANGETEAMPHOTOREQUEST_H
#define CHANGETEAMPHOTOREQUEST_H

#include "irequest.h"

class ChangeTeamPhotoRequest : public IRequest
{
public:
    ChangeTeamPhotoRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // CHANGETEAMPHOTOREQUEST_H
