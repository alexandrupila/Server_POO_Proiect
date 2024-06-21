#include "sendmessagerequest.h"
#include "queryhandler.h"
#include "textmessage.h"
#include "filemessage.h"

SendMessageRequest::SendMessageRequest() {}

void SendMessageRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    IMessage* new_message;

    //sa se verifice daca user ul este in chat

    int user_id=request["user_id"].toInt();
    int chat_id=request["chat_id"].toInt();

    if(!qh.isInChat(user_id,chat_id)) return;

    if(request.value("filename").isUndefined())
    {
        new_message=new TextMessage;
    }
    else
    {
        new_message=new FileMessage;
        new_message->deserialize(request);

        int message_id=qh.addMessage(new_message);

        new_message=qh.retrieveSpecificMessage(message_id);

        QJsonObject jsonObj=new_message->serialize().object();

        IResponse* resp=new OkResponse(jsonObj,"create chat_file");
        resp->sendResponse(clientSocket);
        return;
    }

    new_message->deserialize(request);
    qh.addMessage(new_message);

    //TO DO? Eventual un fel de response???


}
