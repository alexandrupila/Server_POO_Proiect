#include "datatransferhandler.h"
#include "logger.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "loginrequest.h"
#include "registerrequest.h"
#include "updateprofilerequest.h"
#include "createdirectmessagechatrequest.h"
#include "exception.h"

DataTransferHandler::DataTransferHandler() {}

void DataTransferHandler::readClientData()
{
    QByteArray data = clientSocket->readAll();

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);

    try
    {
        if(error.error!=QJsonParseError::NoError)
        {
            Exception exceptie("Error parsing JSON");
            qDebug()<<data;
            qDebug()<<error.errorString();
            exceptie.raise();
        }
    }
    catch(Exception& exceptie)
    {
        Logger::logError(exceptie.what());
        return;
    }

    QJsonObject jsonObj;

    if (jsonDoc.isObject()) {
        jsonObj = jsonDoc.object();
        qDebug() << "Received JSON:" << jsonObj;
    } else {
        qDebug() << "Received data is not JSON object.";
        return;
    }

    IRequest* receivedRequest;

    if(jsonObj.value("request_type")=="register")
    {
        receivedRequest=new RegisterRequest;
    }
    else if(jsonObj.value("request_type")=="login")
    {
        receivedRequest=new LoginRequest;
    }
    else if(jsonObj.value("request_type")=="update_profile")
    {
        receivedRequest= new UpdateProfileRequest;
    }
    else if(jsonObj.value("request_type")=="create direct_chat")
    {
        receivedRequest=new CreateDirectMessageChatRequest;
    }

    else return;

    receivedRequest->processRequest(jsonObj,clientSocket);
}

void DataTransferHandler::sendDataToClient(const QByteArray &data)
{
    qDebug()<<"sending data to client "<<clientSocket->socketDescriptor();
    clientSocket->write(data);
}
