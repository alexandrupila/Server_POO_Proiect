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

User::User(int user_id, QString username, QString email, QString password, QString photo)
{
    this->id=user_id;
    this->username=username;
    this->email=email;
    this->password=password;
    this->base64photo=photo;
}

QJsonDocument User::serialize()
{
    QJsonObject jsonObj;
    jsonObj["username"]=this->username;
    jsonObj["id"]=this->id;
    jsonObj["email"]=this->email;
    jsonObj["password"]=this->password;
    jsonObj["photo"]=this->base64photo;

    QJsonDocument jsonDocument(jsonObj);

    return  jsonDocument;
}

void User::deserialize(QJsonObject &receivedObj)
{
    this->username=receivedObj["username"].toString();
    this->id=receivedObj["id"].toInt();
}
