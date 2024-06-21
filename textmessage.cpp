#include "textmessage.h"
#include "qjsonobject.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

TextMessage::TextMessage() {}

TextMessage::TextMessage(QString content, int sender_id, int chat_id,QString date, int message_id)
{
    this->content=content;
    this->sender_id=sender_id;
    this->chat_id=chat_id;
    this->message_id=message_id;
    this->date=date;
}

QJsonDocument TextMessage::serialize()
{
    QJsonObject jsonObj;
    jsonObj["chat_id"]=this->chat_id;
    jsonObj["user_id"]=this->sender_id;
    jsonObj["message_id"]=this->message_id;
    jsonObj["message"]=this->content;
    jsonObj["time"]=this->date;
    jsonObj["sender_name"]=this->sender_name;
    jsonObj["message_type"]="text_message";

    QJsonDocument jsonDocument(jsonObj);

    return  jsonDocument;
}

void TextMessage::deserialize(QJsonObject &receivedObj)
{
    this->chat_id=receivedObj["chat_id"].toInt();
    this->sender_id=receivedObj["user_id"].toInt();
    this->message_id=receivedObj["message_id"].toInt();
    this->content=receivedObj["message"].toString();
    this->date=receivedObj["time"].toString();
}
