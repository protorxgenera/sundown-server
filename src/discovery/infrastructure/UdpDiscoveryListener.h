#pragma once
#include <QUdpSocket>

#include "../ports/IDiscoveryListener.h"

class UdpDiscoveryListener : public IDiscoveryListener
{
        Q_OBJECT

    public:
        explicit UdpDiscoveryListener(quint16 listenPort, QObject *parent = nullptr);

        void start() override;
        void stop() override;
    private slots:
        void onReadyRead();

    private:
        QUdpSocket m_socket;
        quint16 m_listenPort;
};
