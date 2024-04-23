#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QtWidgets>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>


class IRequest;

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    static MyTcpServer& getInstance();
    static void destroyInstance();
    void incomingConnection(qintptr socketDescriptor) override;
    void processJsonData(const QByteArray &jsonData,QTcpSocket* clientSocket);
protected:

private:
    static MyTcpServer* instance;
    MyTcpServer(const MyTcpServer&) {}
    MyTcpServer(QObject *parent = nullptr) : QTcpServer(parent) {}
    ~MyTcpServer() {}
    QList<QTcpSocket *> clients;
public slots:
    void readClientData(QTcpSocket* clientSocket);
    void handleClientDisconnected();
    void sendDataToClients(const QByteArray &data);
    void sendDataToClient(const QByteArray &data, qintptr clientSocketDescriptor);
    void handleClientConnected(QTcpSocket* clientSocket);

};

#endif // MYTCPSERVER_H
