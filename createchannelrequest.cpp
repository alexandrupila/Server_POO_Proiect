#include "createchannelrequest.h"

CreateChannelRequest::CreateChannelRequest() {}

void CreateChannelRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();
    QString channel_name=request["channel_name"].toString();

    IResponse* resp=nullptr;

    if(qh.isAdmin(user_id,team_id))
    {
        int channel_id=qh.createChannel(user_id,team_id,channel_name,request["channel_type"].toString());
        QJsonObject jsonObj=qh.retrieveChannel(channel_id)->serialize().object();

        if(request["channel_type"]=="public_channel")
        {
            resp=new OkResponse(jsonObj,"create public_channel");
        }
        else
        {
            resp=new OkResponse(jsonObj,"create private_channel");
        }

    }
    else
    {
        //trimite raspuns ca user ul nu este admin
        resp=new ErrorResponse();
    }

    resp->sendResponse(clientSocket);

}
