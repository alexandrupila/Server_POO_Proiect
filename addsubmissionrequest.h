#ifndef ADDSUBMISSIONREQUEST_H
#define ADDSUBMISSIONREQUEST_H

#include "irequest.h"

class AddSubmissionRequest : public IRequest
{
public:
    AddSubmissionRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;
};

#endif // ADDSUBMISSIONREQUEST_H
