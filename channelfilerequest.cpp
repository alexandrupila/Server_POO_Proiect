#include "channelfilerequest.h"

ChannelFileRequest::ChannelFileRequest() {}

void ChannelFileRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();
    int message_id=request["message_id"].toInt();

    IMessage* filemess=qh.retrieveSpecificMessage(message_id);

    IResponse* resp=new OkResponse(filemess->serialize().object(),"open chat_file"); // ce schimb aici?
    resp->sendResponse(clientSocket);
}
