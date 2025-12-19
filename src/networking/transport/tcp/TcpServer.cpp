#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    auto* socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    auto* session = new TcpSession(socket, this);
    emit sessionCreated(session);
}
