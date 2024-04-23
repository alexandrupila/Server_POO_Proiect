#include "registerrequest.h"
#include "mytcpserver.h"
#include "user.h"
#include "queryhandler.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
RegisterRequest::RegisterRequest() {}


void RegisterRequest::processRequest(QJsonObject request,QTcpSocket* clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    QString email=request.value("email").toString();
    QString password=request.value("password").toString();
    QString username=request.value("username").toString();

    qDebug()<<"email:"<<email<<"\n";
    qDebug()<<"username:"<<username<<"\n";
    qDebug()<<"password:"<<password<<"\n";

    //query in baza de date daca user-ul exista deja
    //daca nu exista, sa se creeze un user nou

    if(qh.userExists(email,username,password)==0)
    {
        User user_nou(0,username,email,password);
        qh.insertUser(user_nou);

        user_nou=qh.retrieveNewUser(email);
        MyTcpServer::getInstance().sendDataToClient(user_nou.serialize().toJson(),clientSocket->socketDescriptor());

        qDebug()<<"userul nu exista, s-au adaugat datele\n";

        return;
    }

    //TODO: Mesaj de eroare daca username/email sunt deja existente
    //MyTcpServer::getInstance().sendDataToClient(user_nou.serialize().toJson(),clientSocket->socketDescriptor());

}




