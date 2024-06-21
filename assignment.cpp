#include "assignment.h"
#include "qjsonarray.h"

Assignment::Assignment() {}

Assignment::Assignment(const Assignment &other)
{
    this->assignment_id=other.assignment_id;
    this->assignment_name=other.assignment_name;
    this->creator_id=other.creator_id;
    this->description=other.description;
    this->due_date=other.due_date;
    this->team_id=other.team_id;
    for(auto subm_it:other.submissions)
    {
        this->submissions.append(subm_it);
    }
}

QJsonDocument Assignment::serialize()
{
    QJsonObject jsonObject;
    jsonObject["assigment_name"]=this->assignment_name;
    jsonObject["descriere"]=this->description;
    jsonObject["zi"]=QString::number(this->due_date.day());
    jsonObject["luna"]=QString::number(this->due_date.month());
    jsonObject["an"]=QString::number(this->due_date.year());
    jsonObject["user_id"]=this->creator_id;
    jsonObject["team_id"]=this->team_id;
    jsonObject["assigment_id"]=this->assignment_id;
    QJsonArray submissionarray;
    for(auto subm_it:this->submissions)
    {
        QJsonObject submobj=subm_it->serialize().object();
        submissionarray.append(submobj);
    }
    jsonObject["submissions"]=submissionarray;

    QJsonDocument jsonDoc(jsonObject);

    return jsonDoc;
}

void Assignment::deserialize(QJsonObject &receivedObj)
{
    this->assignment_name=receivedObj["assigment_name"].toString();
    this->description=receivedObj["descriere"].toString();
    int zi=receivedObj["zi"].toString().toInt();
    int luna=receivedObj["luna"].toString().toInt();
    int an=receivedObj["an"].toString().toInt();
    QDate date(an,luna,zi);
    this->team_id=receivedObj["team_id"].toInt();
    this->due_date=date;
    this->creator_id=receivedObj["user_id"].toInt();
    this->assignment_id=receivedObj["assigment_id"].toInt();
    QJsonArray submarray=receivedObj["submissions"].toArray();
    for(auto subm_it:submarray)
    {
        QJsonObject submobj=subm_it.toObject();
        Submission* subm=new Submission;
        subm->deserialize(submobj);
        this->submissions.append(subm);
    }
}

