#ifndef ACHAT_H
#define ACHAT_H

#include "ichat.h"
#include "user.h"
#include "textmessage.h"
#include "filemessage.h"

class AChat : public IChat
{
public:
    AChat();
    AChat(int id) {chat_id=id;}
    void addUser(User user_to_add) override;
    void addMessage(IMessage* new_message) override;
protected:
    int chat_id;
    QString chat_name;
    QVector<User> user_list;
    QVector<IMessage*> message_list;
};

#endif // ACHAT_H
