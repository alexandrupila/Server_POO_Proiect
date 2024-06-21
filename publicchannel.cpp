#include "publicchannel.h"

PublicChannel::PublicChannel() {this->channel_chat=new GroupChat;}

QJsonDocument PublicChannel::serialize()
{
    QJsonObject jsonObj;

    jsonObj["channel_type"]="public_channel";

    jsonObj["channel_id"]=this->channel_id;
    jsonObj["channel_name"]=this->channel_name;
    jsonObj["channel_chat"]=this->channel_chat->serialize().object();

    QJsonDocument jsonDoc(jsonObj);

    return jsonDoc;

}

void PublicChannel::deserialize(QJsonObject &receivedObj)
{

}
