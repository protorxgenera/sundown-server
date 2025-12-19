#pragma once
#include <QObject>
#include <QTcpSocket>
#include "../../messaging/domain/ProtocolMessage.h"

class TcpSession : public QObject
{
        Q_OBJECT

    public:
        explicit TcpSession(QTcpSocket* socket, QObject* parent = nullptr);

        void send(const QByteArray& data);

        signals:
        void messageReceived(const ProtocolMessage& msg);

    private:
        QTcpSocket* m_socket;
};
