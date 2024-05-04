#ifndef OKDIRECTCHATRESPONSE_H
#define OKDIRECTCHATRESPONSE_H

#include "iresponse.h"
#include "directmessagechat.h"

class OkDirectChatResponse : public IResponse
{
public:
    OkDirectChatResponse();
    OkDirectChatResponse(DirectMessageChat* chat)
    {
        chat_de_trimis=chat;
    }
    void sendResponse(QTcpSocket* clientsocket);
protected:
    DirectMessageChat* chat_de_trimis;
};

#endif // OKDIRECTCHATRESPONSE_H
