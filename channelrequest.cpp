#include "channelrequest.h"

ChannelRequest::ChannelRequest() {}

void ChannelRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();
    int channel_id=request["channel_id"].toInt();

    IChannel* requested_channel=qh.retrieveChannel(channel_id);

    QJsonObject obj=requested_channel->serialize().object();
    obj["request_type"]="channel";

    QJsonDocument doc(obj);

    DataTransferHandler* datahandler=new DataTransferHandler(clientSocket);
    datahandler->sendDataToClient(doc.toJson());
}
