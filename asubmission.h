#ifndef ASUBMISSION_H
#define ASUBMISSION_H

#include "isubmission.h"

class ASubmission : public ISubmission
{
public:
    ASubmission();
    QJsonDocument serialize();
    void deserialize(QJsonObject& receivedObj);
protected:
    int submission_id;
    int user_id;
    QString filename;
    QString file_content;
    //maybe clasa pentru fisiere?
    int grade;
};

#endif // ASUBMISSION_H
