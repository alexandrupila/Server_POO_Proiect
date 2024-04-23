#include "mytcpserver.h"
#include "irequest.h"
#include "registerrequest.h"
#include "loginrequest.h"
#include "updateprofilerequest.h"
#include "createdirectmessagechatrequest.h"
#include "Logger.h"
#include "clientthread.h"

MyTcpServer* MyTcpServer::instance=nullptr;

MyTcpServer &MyTcpServer::getInstance()
{
    if(!MyTcpServer::instance)
    {
        MyTcpServer::instance=new MyTcpServer();
    }
    return (*MyTcpServer::instance);
}

void MyTcpServer::destroyInstance()
{
    if(MyTcpServer::instance)
    {
        delete MyTcpServer::instance;
        MyTcpServer::instance=nullptr;
    }
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        clients.append(clientSocket);

        connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
            readClientData(clientSocket);
        });

        connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::handleClientDisconnected);

        Logger::logConnection("Client connected with descriptor:"+QString::number(socketDescriptor));


    } else {
        delete clientSocket;
    }
    /*
    ClientThread *clientThread = new ClientThread(socketDescriptor, this);

    connect(clientThread, &ClientThread::clientConnected, this, &MyTcpServer::handleClientConnected);
    connect(clientThread, &ClientThread::clientDisconnected, this, &MyTcpServer::handleClientDisconnected);

    clientThread->start();
*/

}


void MyTcpServer::processJsonData(const QByteArray &jsonData,QTcpSocket* clientSocket)
{
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << error.errorString();
        return;
    }

    QJsonObject jsonObj;

    if (jsonDoc.isObject()) {
        jsonObj = jsonDoc.object();
        qDebug() << "Received JSON:" << jsonObj;
    } else {
        qDebug() << "Received data is not JSON object.";
    }

    IRequest* receivedRequest;

    // if(jsonObj.value("Request_type")=="Login")
    // {
    //     QJsonObject tempObj;
    //     tempObj["Login"]="ok";
    //     qDebug()<<"Sending json: "<<tempObj;
    //     QJsonDocument doc(tempObj);

    //     MyTcpServer::sendDataToClient(doc.toJson(),clientSocket->socketDescriptor());
    //     return;
    // }
    // else if(jsonObj.value("Request_type")=="Register")
    // {
    //     QJsonObject tempObj;
    //     tempObj["Register"]="ok";
    //     qDebug()<<"Sending json: "<<tempObj;
    //     QJsonDocument doc(tempObj);

    //     MyTcpServer::sendDataToClient(doc.toJson(),clientSocket->socketDescriptor());
    //     return;
    // }
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
    else if(jsonObj.value("request_type")=="direct_chat")
    {
        receivedRequest=new CreateDirectMessageChatRequest;
    }

    else return;

    receivedRequest->processRequest(jsonObj,clientSocket);


}

void MyTcpServer::readClientData(QTcpSocket *clientSocket)
{
    QByteArray data = clientSocket->readAll();

    MyTcpServer::getInstance().processJsonData(data,clientSocket);
}

void MyTcpServer::handleClientDisconnected()
{

}

void MyTcpServer::sendDataToClients(const QByteArray &data)
{

}

void MyTcpServer::sendDataToClient(const QByteArray &data, qintptr clientSocketDescriptor)
{

    qDebug()<<"Sending data to client "<<clientSocketDescriptor<<"\n";
    foreach (QTcpSocket *clientSocket, clients) {
        if (clientSocket->socketDescriptor() == clientSocketDescriptor) {
            if (clientSocket->write(data) == -1) {
                qDebug() << "Failed to send data to client with descriptor:" << clientSocketDescriptor;
            }
            return;
        }
    }

    qDebug() << "Client with descriptor" << clientSocketDescriptor << "not found!";

}

void MyTcpServer::handleClientConnected(QTcpSocket *clientSocket)
{
    if (clientSocket->setSocketDescriptor(clientSocket->socketDescriptor())) {
        // Add the client socket to the list of connected clients
        clients.append(clientSocket);

        // Connect signals for reading data and handling disconnection
        connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
            readClientData(clientSocket);
        });
        connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::handleClientDisconnected);

        // Log the client connection
        Logger::logConnection("Client connected with descriptor:" + QString::number(clientSocket->socketDescriptor()));

        // Perform any other initialization tasks, if needed
    } else {
        delete clientSocket;
    }
}

