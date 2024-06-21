#include "chatuserlistrequest.h"

ChatUserListRequest::ChatUserListRequest() {}

void ChatUserListRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int chat_id=request["chat_id"].toInt();
    int user_id=request["user_id"].toInt();

    if(qh.isCreator(user_id,chat_id))
    {
        QVector<IUser*> users=qh.retrieveUsersInChat(chat_id);

        QJsonObject jsonObj;

        QJsonArray usersArray;
        for(auto user_it: users)
        {
            QJsonObject user_obj=user_it->serialize().object();
            usersArray.append(user_obj);
        }
        jsonObj["users"]=usersArray;
        jsonObj["request_type"]="user_list";
        jsonObj["chat_id"]=chat_id;

        QJsonDocument jsonDoc(jsonObj);


        DataTransferHandler* datahandler=new DataTransferHandler(clientSocket);
        datahandler->sendDataToClient(jsonDoc.toJson());
    }
    else
    {
        IResponse* resp=new ErrorResponse();
        resp->sendResponse(clientSocket);
    }
}
