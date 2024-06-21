#ifndef GRADESUBMISSIONREQUEST_H
#define GRADESUBMISSIONREQUEST_H

#include "irequest.h"

class GradeSubmissionRequest : public IRequest
{
public:
    GradeSubmissionRequest();
    void processRequest(QJsonObject request,QTcpSocket* clientSocket) override;

};

#endif // GRADESUBMISSIONREQUEST_H
