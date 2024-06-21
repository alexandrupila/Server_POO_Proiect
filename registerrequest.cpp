#include "registerrequest.h"
#include "mytcpserver.h"
#include "user.h"
#include "queryhandler.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include "okresponse.h"
#include "errorresponse.h"
RegisterRequest::RegisterRequest() {}


void RegisterRequest::processRequest(QJsonObject request,QTcpSocket* clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    QString email=request.value("email").toString();
    QString password=request.value("password").toString();
    QString username=request.value("username").toString();
    QString base64photo=request.value("photo").toString();

    qDebug()<<"email:"<<email<<"\n";
    qDebug()<<"username:"<<username<<"\n";
    qDebug()<<"password:"<<password<<"\n";

    //query in baza de date daca user-ul exista deja
    //daca nu exista, sa se creeze un user nou

    if(qh.userExists(email,username,password)==0)
    {
        IUser* user_nou=new User(0,username,email,password,base64photo);
        qh.insertUser(user_nou);
        user_nou=qh.retrieveNewUser(email);

        // OkResponse response("valid");
        // response.sendResponse(clientSocket);

        QJsonObject jsonObj;
        jsonObj["request_type"]="register";

        QJsonDocument doc(jsonObj);

        DataTransferHandler* transferHandler=new DataTransferHandler(clientSocket);
        transferHandler->sendDataToClient(doc.toJson());

        qDebug()<<"userul nu exista, s-au adaugat datele\n";

        return;
    }
    else
    {
        QJsonObject jsonObj;
        jsonObj["authentification"]="not ok";

        QJsonDocument doc(jsonObj);

        DataTransferHandler* transferHandler=new DataTransferHandler(clientSocket);
        transferHandler->sendDataToClient(doc.toJson());
    }

    // ErrorResponse response("invalid_credentials");
    // response.sendResponse(clientSocket);


}




