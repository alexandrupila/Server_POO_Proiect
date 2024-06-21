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
    jsonObj["assigment_id"]=this->submission_id;

    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc;
}

void ASubmission::deserialize(QJsonObject &receivedObj)
{
    this->submission_id=receivedObj["submission_id"].toInt();
    this->assignment_id=receivedObj["assigment_id"].toInt();
    this->user_id=receivedObj["user_id"].toInt();
    this->filename=receivedObj["filename"].toString();
    this->file_content=receivedObj["file_content"].toString();
    this->grade=receivedObj["grade"].toInt();
}
