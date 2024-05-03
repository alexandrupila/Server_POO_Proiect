#include "filemessage.h"

FileMessage::FileMessage() {}

FileMessage::FileMessage(File file, int sender_id, int chat_id, int message_id)
{
    this->file=file;
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

    QJsonDocument jsonedFileDoc=this->file.serialize();
    QJsonObject jsonedFileObj=jsonedFileDoc.object();

    for(auto it=jsonedFileObj.begin();it!=jsonedFileObj.end();++it)
    {
        jsonObj.insert(it.key(),it.value());
    }

    QJsonDocument jsonDocument(jsonObj);

    return  jsonDocument;
}

void FileMessage::deserialize(QJsonObject &receivedObj)
{

}
