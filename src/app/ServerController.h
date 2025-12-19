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

        void handlePairingRequest(TcpSession* session, const ProtocolMessage& msg);

        void sendError(TcpSession* session, const QString& reason);

    public slots:
        void onServerDiscovered(const DiscoveryPacket &packet);

        void onSessionCreated(TcpSession *session);

        void onMessageReceived(TcpSession *session, const ProtocolMessage &msg);

    private:
        DiscoveryBroadcaster m_broadcaster;
        UdpDiscoveryListener m_discoveryListener;
        DiscoveredServerRegistry m_registry;
        TcpServer m_tcpServer;
        ServerState m_state;
};
