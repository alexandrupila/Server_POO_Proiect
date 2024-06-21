#include "directmessagechat.h"
#include <QJsonArray>

DirectMessageChat::DirectMessageChat() {}

QJsonDocument DirectMessageChat::serialize()
{
    QJsonObject jsonObj;
    jsonObj["chat_id"]=this->chat_id;
    jsonObj["request_type"]="direct_chat";
    jsonObj["chat_type"]="direct_chat";
    jsonObj["request_type"]="direct_chat";
    //de test
    jsonObj["chat_name"]=this->chat_name;

    QJsonArray usersArray;
    for(auto user_it: user_list)
    {
        QJsonObject user_obj=user_it->serialize().object();
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

