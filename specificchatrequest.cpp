#include "specificchatrequest.h"

SpecificChatRequest::SpecificChatRequest() {}

void SpecificChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int chat_id=request.value("chat_id").toInt();

    if(qh.chatExists(chat_id))
    {
        IChat* chat=qh.retrieveSpecificChat(chat_id);

        DataTransferHandler* datahandler=new DataTransferHandler(clientSocket);
        datahandler->sendDataToClient(chat->serialize().toJson());
    }

}
