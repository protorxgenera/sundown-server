#pragma once
#include "../networking/discovery/domain/DiscoveredServerRegistry.h"
#include "../networking/discovery/infrastructure/DiscoveryBroadcaster.h"
#include "../networking/discovery/infrastructure/UdpDiscoveryListener.h"
#include "../networking/session/messaging/domain/StateSnapshot.h"
#include "../networking/session/domain/SessionId.h"
#include "../networking/session/domain/SessionManager.h"

/**
 * Owns: application behavior (pairing, scheduling, shutdown).
 */

class ServerController : public QObject
{
        Q_OBJECT

    public:
        explicit ServerController(QObject *parent = nullptr);

        const DiscoveredServerRegistry& registry() const {return m_registry; }

        void start();
        void stop();

    public slots:
        void onSessionConnected(SessionId id);
        void onSessionDisconnected(SessionId id);
        void onProtocolMessage(SessionId id, const ProtocolMessage& msg);
        void onServerDiscovered(const DiscoveryPacket& packet);

    private:
        void handlePairingRequest(SessionId id, const ProtocolMessage& msg);
        void sendError(SessionId id, const QString& reason);

        DiscoveryBroadcaster m_broadcaster;
        UdpDiscoveryListener m_discoveryListener;
        DiscoveredServerRegistry m_registry;
        SessionManager m_sessions;
        StateSnapshot m_state;
};
