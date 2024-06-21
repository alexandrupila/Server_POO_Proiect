#include "filemessage.h"

FileMessage::FileMessage() {}

FileMessage::FileMessage(QString filename, QString file_content, int sender_id, int chat_id,QString date, int message_id)
{
    this->filename=filename;
    this->file_content=file_content;
    this->sender_id=sender_id;
    this->chat_id=chat_id;
    this->message_id=message_id;
    this->date=date;
}

QJsonDocument FileMessage::serialize()
{
    QJsonObject jsonObj;
    jsonObj["message_type"]="file_message";
    jsonObj["chat_id"]=this->chat_id;
    jsonObj["user_id"]=this->sender_id;
    jsonObj["message_id"]=this->message_id;
    jsonObj["filename"]=this->filename;
    jsonObj["content"]=this->file_content;
    jsonObj["time"]=this->date;
    jsonObj["sender_name"]=this->sender_name;


    QJsonDocument jsonDocument(jsonObj);

    return  jsonDocument;
}

void FileMessage::deserialize(QJsonObject &receivedObj)
{
    this->chat_id=receivedObj["chat_id"].toInt();
    this->sender_id=receivedObj["user_id"].toInt();
    this->message_id=receivedObj["message_id"].toInt();
    this->filename=receivedObj["filename"].toString();
    this->file_content=receivedObj["content"].toString();
    this->date=receivedObj["time"].toString();
}
