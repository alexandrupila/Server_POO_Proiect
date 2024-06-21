#include "specificteamrequest.h"

SpecificTeamRequest::SpecificTeamRequest() {}

void SpecificTeamRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();

    ITeam* requested_team=qh.retrieveTeam(team_id);
    if(qh.isAdmin(user_id,team_id))
    {
        requested_team->setChannelList(qh.retrieveChannels(team_id));
    }
    else requested_team->setChannelList(qh.retrievePublicChannels(team_id));

    QJsonObject jsonObj=requested_team->serialize().object();

    jsonObj["request_type"]="team";
    jsonObj["is_admin"]=qh.isAdmin(user_id,team_id);



    QJsonDocument jsonDoc(jsonObj);

    DataTransferHandler* datahandler=new DataTransferHandler(clientSocket);
    datahandler->sendDataToClient(jsonDoc.toJson());
}
