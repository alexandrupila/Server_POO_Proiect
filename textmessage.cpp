#include "textmessage.h"
#include "qjsonobject.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

TextMessage::TextMessage() {}

TextMessage::TextMessage(QString content, int sender_id, int chat_id, int message_id)
{
    this->content=content;
    this->sender_id=sender_id;
    this->chat_id=chat_id;
    this->message_id=message_id;
}

QJsonDocument TextMessage::serialize()
{
    QJsonObject jsonObj;
    jsonObj["chat_id"]=this->chat_id;
    jsonObj["sender_id"]=this->sender_id;
    jsonObj["message_id"]=this->message_id;
    jsonObj["content"]=this->content;

    QJsonDocument jsonDocument(jsonObj);

    return  jsonDocument;
}

void TextMessage::deserialize(QJsonObject &receivedObj)
{

}
