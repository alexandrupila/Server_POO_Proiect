#include "okdirectchatresponse.h"
#include "datatransferhandler.h"

OkDirectChatResponse::OkDirectChatResponse() {}

void OkDirectChatResponse::sendResponse(QTcpSocket *clientsocket)
{
    QJsonObject jsonObj;
    jsonObj["result"]="ok";
    jsonObj["validation_type"]="create direct_chat";

    QJsonObject serialized_chat=this->chat_de_trimis->serialize().object();

    for(auto it=serialized_chat.begin();it!=serialized_chat.constEnd();++it)
    {
        jsonObj.insert(it.key(),it.value());
    }
    jsonObj["request_type"]="validare";

    QJsonDocument jsonDoc(jsonObj);

    DataTransferHandler* transferHandler=new DataTransferHandler(clientsocket);
    transferHandler->sendDataToClient(jsonDoc.toJson());
}
