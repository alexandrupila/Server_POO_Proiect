#include "aassignment.h"

AAssignment::AAssignment() {}

//TO DO: adaugat serializarea pentru submission-uri???

QJsonDocument AAssignment::serialize()
{
    QJsonObject jsonObj;

    jsonObj["assignment_id"]=this->assignment_id;
    jsonObj["assignment_name"]=this->assignment_name;
    jsonObj["creator_id"]=this->creator_id;
    jsonObj["due_date"]=this->due_date.toString();
    jsonObj["description"]=this->description;

    QJsonDocument jsonDoc(jsonObj);
    return QJsonDocument();

}

void AAssignment::deserialize(QJsonObject &receivedObj)
{

}
