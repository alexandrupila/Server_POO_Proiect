#include "chatsrequest.h"
#include "queryhandler.h"
#include "mytcpserver.h"
ChatsRequest::ChatsRequest() {}

void ChatsRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request.value("user_id").toInt();

    QVector<IChat*> chats=qh.retrieveChats(user_id);

    QJsonObject obj;
    QJsonArray chatsarray;

    for(IChat* chat_it: chats)
    {
        QJsonObject chat_obj=chat_it->serialize().object();
        chatsarray.append(chat_obj);
    }

    obj["chaturi"]=chatsarray;

    obj["request_type"]="chaturi";

    QJsonDocument jsonDoc(obj);

    DataTransferHandler* transferHandler=new DataTransferHandler(clientSocket);
    transferHandler->sendDataToClient(jsonDoc.toJson());


}
