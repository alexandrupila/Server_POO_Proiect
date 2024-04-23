#include "achannel.h"

AChannel::AChannel() {}

QJsonDocument AChannel::serialize()
{
    QJsonObject jsonObj;

    jsonObj["channel_id"]=this->channel_id;
    jsonObj["channel_name"]=this->channel_name;

    QJsonObject jsonedChat=this->channel_chat.serialize().object();
    jsonObj["channel_chat"]=jsonedChat;

}

void AChannel::deserialize(QJsonObject &receivedObj)
{

}
