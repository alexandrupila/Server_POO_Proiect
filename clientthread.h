#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class ClientThread : public QThread
{
    Q_OBJECT
public:
    ClientThread(qintptr socketDescriptor, QObject *parent = nullptr)
        : QThread(parent), m_socketDescriptor(socketDescriptor) {}

protected:
    void run() override {
        QTcpSocket *clientSocket = new QTcpSocket();

        if (clientSocket->setSocketDescriptor(m_socketDescriptor)) {
            // Add the socket to the list of clients
            emit clientConnected(clientSocket);

            // Connect signals/slots for reading data and handling disconnection
            connect(clientSocket, &QTcpSocket::readyRead, this, &ClientThread::readClientData);
            connect(clientSocket, &QTcpSocket::disconnected, this, &ClientThread::handleDisconnect);

            exec(); // Start event loop for this thread
        } else {
            delete clientSocket;
        }
    }

private slots:
    void readClientData() {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
        if (!clientSocket)
            return;

        // Read and process data from the client socket
        // Example: readClientData(clientSocket->readAll());
    }

    void handleDisconnect() {
        // Emit signal indicating client disconnection
        emit clientDisconnected();
        // Exit the thread event loop
        exit();
    }

signals:
    void clientConnected(QTcpSocket *clientSocket);
    void clientDisconnected();

private:
    qintptr m_socketDescriptor;
};

#endif // CLIENTTHREAD_H
