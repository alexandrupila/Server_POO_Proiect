#include "groupchat.h"
#include "QJsonArray"

GroupChat::GroupChat() {}

QJsonDocument GroupChat::serialize()
{
    QJsonObject jsonObj;
    jsonObj["chat_id"]=this->chat_id;
    jsonObj["creator_id"]=this->creator_id;
    jsonObj["chat_type"]="group_chat";
    jsonObj["request_type"]="group_chat";
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
