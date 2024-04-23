#include "asubmission.h"

ASubmission::ASubmission() {}

QJsonDocument ASubmission::serialize()
{
    QJsonObject jsonObj;

    jsonObj["submission_id"]=this->submission_id;
    jsonObj["user_id"]=this->user_id;
    jsonObj["filename"]=this->filename;
    jsonObj["file_content"]=this->file_content;
    jsonObj["grade"]=this->grade;

    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc;
}

void ASubmission::deserialize(QJsonObject &receivedObj)
{

}
