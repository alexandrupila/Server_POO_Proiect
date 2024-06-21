#include "achat.h"

AChat::AChat() {}

void AChat::addUser(IUser* user_to_add)
{
    this->user_list.push_back(user_to_add);
}

void AChat::addMessage(IMessage *new_message)
{
    this->message_list.push_back(new_message);
}

void AChat::setUserList(QVector<IUser*>users)
{
    this->user_list=users;
}

void AChat::setMessageList(QVector<IMessage *> messages)
{
    this->message_list=messages;
}
