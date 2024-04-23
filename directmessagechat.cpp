#include "directmessagechat.h"
#include <QJsonArray>

DirectMessageChat::DirectMessageChat() {}

QJsonDocument DirectMessageChat::serialize()
{
    QJsonObject jsonObj;
    jsonObj["chat_id"]=this->chat_id;
    jsonObj["chat_type"]="direct";

    QJsonArray usersArray;
    for(User user_it: user_list)
    {
        QJsonObject user_obj=user_it.serialize().object();
        usersArray.append(user_obj);
    }
    jsonObj["users"]=usersArray;

    QJsonArray messagesArray;
    for(IMessage* message_it:message_list)
    {
        QJsonObject message_obj=message_it->serialize().object();
        messagesArray.append(message_obj);
    }
    jsonObj["messages"]=messagesArray;

    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc;
}

void DirectMessageChat::deserialize(QJsonObject &receivedObj)
{

}
