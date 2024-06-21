#include "privatechannel.h"

PrivateChannel::PrivateChannel() {this->channel_chat=new GroupChat;}

QJsonDocument PrivateChannel::serialize()
{
    QJsonObject jsonObj;

    jsonObj["channel_type"]="private_channel";

    jsonObj["channel_id"]=this->channel_id;
    jsonObj["channel_name"]=this->channel_name;
    jsonObj["channel_chat"]=this->channel_chat->serialize().object();

    QJsonDocument jsonDoc(jsonObj);

    return jsonDoc;
}

void PrivateChannel::deserialize(QJsonObject &receivedObj)
{

}
