#pragma once
#include <QObject>
#include <QTcpSocket>

class TcpSession : public QObject
{
        Q_OBJECT

    public:
        explicit TcpSession(QTcpSocket* socket, QObject* parent = nullptr);

        void send(const QByteArray& data);

    private:
        QTcpSocket* m_socket;
};
