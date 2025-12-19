#pragma once
#include "../discovery/infrastructure/DiscoveryBroadcaster.h"
#include "../discovery/infrastructure/UdpDiscoveryListener.h"


class ServerController : public QObject
{
        Q_OBJECT

    public:
        explicit ServerController(QObject *parent = nullptr);

        void start();

        void stop();

    public slots:
        void onServerDiscovered(const DiscoveryPacket& packet);

    private:
        DiscoveryBroadcaster m_broadcaster;
        UdpDiscoveryListener m_discoveryListener;
};
