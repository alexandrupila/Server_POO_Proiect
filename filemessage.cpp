#include "filemessage.h"

FileMessage::FileMessage() {}

FileMessage::FileMessage(QString filename, QString filecontent, int sender_id, int chat_id, int message_id)
{
    this->filename=filename;
    this->filecontent=filecontent;
    this->sender_id=sender_id;
    this->chat_id=chat_id;
    this->message_id=message_id;
}

QJsonDocument FileMessage::serialize()
{
    QJsonObject jsonObj;
    jsonObj["chat_id"]=this->chat_id;
    jsonObj["sender_id"]=this->sender_id;
    jsonObj["message_id"]=this->message_id;
    jsonObj["filename"]=this->filename;
    jsonObj["file_content"]=this->filecontent;

    QJsonDocument jsonDocument(jsonObj);

    return  jsonDocument;
}

void FileMessage::deserialize(QJsonObject &receivedObj)
{

}
