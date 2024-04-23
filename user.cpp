#include "user.h"
#include "qjsonobject.h"
#include "ichat.h"
#include <QJsonDocument>

User::User(){}

User::User(const User &other)
{
    this->username=other.username;
    this->email=other.email;
    this->password=other.password;
    this->id=other.id;
}

QJsonDocument User::serialize()
{
    QJsonObject jsonObj;
    jsonObj["username"]=this->username;
    jsonObj["id"]=this->id;
    jsonObj["email"]=this->email;
    jsonObj["password"]=this->password;
    jsonObj["request_type"]="user";

    QJsonDocument jsonDocument(jsonObj);

    return  jsonDocument;
}

void User::deserialize(QJsonObject &receivedObj)
{
    this->username=receivedObj["username"].toString();
    this->id=receivedObj["id"].toInt();
}
