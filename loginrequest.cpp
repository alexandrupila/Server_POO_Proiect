#include "loginrequest.h"
#include "user.h"
#include "mytcpserver.h"
#include "queryhandler.h"

LoginRequest::LoginRequest() {}

void LoginRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
     QueryHandler& qh=QueryHandler::getInstance();

    QString email=request.value("email").toString();
    QString password=request.value("password").toString();

    qDebug()<<"email:"<<email<<"\n";
    qDebug()<<"password:"<<password<<"\n";

    //query in baza de date daca user-ul exista deja
    //daca nu exista, sa se creeze un user nou


    if(!qh.checkCredentials(email,password))
    {
        return;
    }


    User user_nou=qh.retrieveNewUser(email);

    MyTcpServer::getInstance().sendDataToClient(user_nou.serialize().toJson(),clientSocket->socketDescriptor());

}
