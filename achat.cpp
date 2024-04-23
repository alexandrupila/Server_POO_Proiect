#include "achat.h"

AChat::AChat() {}

void AChat::addUser(User user_to_add)
{
    this->user_list.push_back(user_to_add);
}

void AChat::addMessage(IMessage *new_message)
{
    this->message_list.push_back(new_message);
}
