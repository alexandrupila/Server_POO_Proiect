#ifndef DATATRANSFERHANDLER_H
#define DATATRANSFERHANDLER_H

#include <QObject>
#include <QTcpSocket>

class DataTransferHandler
{
protected:
    QTcpSocket* clientSocket;
public:
    DataTransferHandler();
    DataTransferHandler(QTcpSocket* socket) {this->clientSocket=socket;}
public slots:
    void readClientData();
    void handleClientDisconnected();
    void sendDataToClients(const QByteArray &data);
    void sendDataToClient(const QByteArray &data);
    void handleClientConnected();
};

#endif // DATATRANSFERHANDLER_H
