#pragma once

#include <QTcpServer>

#include "TcpSession.h"

class TcpServer : public QTcpServer
{
        Q_OBJECT

    public:
        explicit TcpServer(QObject *parent = nullptr);

    signals:
        void sessionCreated(TcpSession *session);

    protected:
        void incomingConnection(qintptr socketDescriptor) override;
};
