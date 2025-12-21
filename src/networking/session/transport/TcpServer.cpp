#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    connect(&m_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

bool TcpServer::start(quint16 port)
{
    return m_server.listen(QHostAddress::Any, port);
}

void TcpServer::stop()
{
    m_server.close();
}

void TcpServer::onNewConnection()
{
    while (m_server.hasPendingConnections())
    {
        QTcpSocket* socket = m_server.nextPendingConnection();

        auto* session = new TcpSession(socket, this);
        emit sessionCreated(session);
    }
}
