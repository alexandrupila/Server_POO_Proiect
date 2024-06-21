#include "submission.h"

Submission::Submission() {}

QJsonDocument Submission::serialize()
{
    QJsonObject jsonobject;
    jsonobject["user_id"]=this->user_id;
    jsonobject["filename"]=this->filename;
    jsonobject["file_content"]=this->file_content;
    jsonobject["grade"]=this->grade;
    jsonobject["submission_id"]=this->submission_id;
    jsonobject["username"]=this->username;

    QJsonDocument jsonDoc(jsonobject);

    return jsonDoc;
}

void Submission::deserialize(QJsonObject &receivedObj)
{
    this->user_id=receivedObj["user_id"].toInt();
    this->submission_id=receivedObj["submission_id"].toInt();
    this->filename=receivedObj["filename"].toString();
    this->file_content=receivedObj["content"].toString();
    this->grade=receivedObj["grade"].toInt();
}
