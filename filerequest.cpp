#include "filerequest.h"

FileRequest::FileRequest() {}

void FileRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();
    int message_id=request["message_id"].toInt();

    IMessage* filemess=qh.retrieveSpecificMessage(message_id);

    IResponse* resp=new OkResponse(filemess->serialize().object(),"open chat_file");
    resp->sendResponse(clientSocket);
}
