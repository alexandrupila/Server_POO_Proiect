#include "teamuserlistrequest.h"

TeamUserListRequest::TeamUserListRequest() {}

void TeamUserListRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();

    if(qh.isAdmin(user_id,team_id))
    {
        QVector<IUser*> users=qh.retrieveUsersInTeam(team_id);

        QJsonObject jsonObj;

        QJsonArray usersArray;
        for(auto user_it: users)
        {
            QJsonObject user_obj=user_it->serialize().object();
            usersArray.append(user_obj);
        }
        jsonObj["users"]=usersArray;
        jsonObj["request_type"]="user_list_for_team";
        jsonObj["team_id"]=team_id;

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
