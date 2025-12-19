#include "TcpSession.h"

TcpSession::TcpSession(QTcpSocket *socket, QObject *parent) : QObject(parent), m_socket(socket)
{
}

void TcpSession::send(const QByteArray& data)
{
    m_socket->write(data);
    m_socket->flush();
}
