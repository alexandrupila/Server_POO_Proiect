#ifndef SUBMISSION_H
#define SUBMISSION_H

#include "asubmission.h"

class Submission : public ASubmission
{
public:
    Submission();
    QJsonDocument serialize();
    void deserialize(QJsonObject& receivedObj);
};

#endif // SUBMISSION_H
