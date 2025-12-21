#pragma once

#include <QTcpServer>

#include "TcpSession.h"

class TcpServer : public QObject
{
        Q_OBJECT

    public:
        explicit TcpServer(QObject *parent = nullptr);

        bool start(quint16 port);
        void stop();

    signals:
        void sessionCreated(TcpSession *session);

    private slots:
        void onNewConnection();

    private:
        QTcpServer m_server;
};
