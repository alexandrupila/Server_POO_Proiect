#include "sendmessagechannelrequest.h"
#include "publicchannel.h"
#include "privatechannel.h"

SendMessageChannelRequest::SendMessageChannelRequest() {}

void SendMessageChannelRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    IMessage* new_message;

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();
    int channel_id=request["channel_id"].toInt();

    IChannel* channel=qh.retrieveChannel(channel_id);

    int chat_id=channel->getChatId();

    IResponse* resp;

    if(!qh.isInTeam(user_id,team_id))
    {
        resp=new ErrorResponse();
        resp->sendResponse(clientSocket);
        return;
    }

    if(dynamic_cast<PrivateChannel*>(channel))
    {
        if(!qh.isAdmin(user_id,team_id))
        {
            resp=new ErrorResponse();
            resp->sendResponse(clientSocket);
            return;
        }
    }
    if(request.value("filename").isUndefined())
    {
        new_message=new TextMessage;
    }
    else
    {
        new_message=new FileMessage;
    }
        new_message->deserialize(request);
        new_message->setChatId(chat_id);
        int message_id=qh.addMessage(new_message);
        new_message=qh.retrieveSpecificMessage(message_id);

        QJsonObject jsonObj=new_message->serialize().object();

        //IResponse* resp=new OkResponse(jsonObj,"create chat_file");
        resp=new OkResponse(jsonObj,"message_channel");
        resp->sendResponse(clientSocket);

}
