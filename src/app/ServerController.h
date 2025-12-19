#pragma once
#include "../networking/discovery/domain/DiscoveredServerRegistry.h"
#include "../networking/discovery/infrastructure/DiscoveryBroadcaster.h"
#include "../networking/discovery/infrastructure/UdpDiscoveryListener.h"
#include "../networking/transport/tcp/TcpServer.h"
#include "../networking/messaging/domain/ServerState.h"


class ServerController : public QObject
{
        Q_OBJECT

    public:
        explicit ServerController(QObject *parent = nullptr);

        void start();

        void stop();

        void simulateDiscovery();

        const DiscoveredServerRegistry &registry() const;

    public slots:
        void onServerDiscovered(const DiscoveryPacket &packet);

        void onSessionCreated(TcpSession *session) const;

        void onMessageReceived(const ProtocolMessage& msg);

    private:
        DiscoveryBroadcaster m_broadcaster;
        UdpDiscoveryListener m_discoveryListener;
        DiscoveredServerRegistry m_registry;
        TcpServer m_tcpServer;
        ServerState m_state;
};
