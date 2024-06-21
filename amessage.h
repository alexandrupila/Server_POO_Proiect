#ifndef AMESSAGE_H
#define AMESSAGE_H

#include "imessage.h"

class AMessage : public IMessage
{
public:
    AMessage();
    int getChatId() override {return this->chat_id;}
    int getSenderId() override {return this->sender_id;}
    int getMessageId() override {return this->message_id;}
    QString getSenderName() override{return this->sender_name;}
    QString getDate() override {return this->date;}
    virtual void setSenderId(int id) override{this->sender_id=id;}
    virtual void setChatId(int id) override{this->chat_id=id;}
    virtual void setSenderName(QString name) override {this->sender_name=name;}
protected:
    int message_id;
    int sender_id;
    int chat_id;
    QString date;
    QString sender_name;
};

#endif // AMESSAGE_H
