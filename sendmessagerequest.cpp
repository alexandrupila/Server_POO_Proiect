#include "sendmessagerequest.h"
#include "queryhandler.h"
#include "textmessage.h"
#include "filemessage.h"

SendMessageRequest::SendMessageRequest() {}

void SendMessageRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
     QueryHandler& qh=QueryHandler::getInstance();

    int sender_id=request.value("sender_id").toInt();
    int chat_id=request.value("chat_id").toInt();

    IMessage* new_message;

    if(request.value("filename").isUndefined())
    {
        QString content=request.value("content").toString();
        new_message=new TextMessage(content,sender_id,chat_id);
    }
    else
    {
        QString filename=request.value("filename").toString();
        QString file_content=request.value("file_content").toString();
        File newfile(filename,file_content);
        new_message=new FileMessage(newfile,sender_id,chat_id);
        //initializare pentru FileMessage
    }

    //todo: bag in baza de date mesajul s
    //


}
