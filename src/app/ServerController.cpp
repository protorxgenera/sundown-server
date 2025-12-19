#include "ServerController.h"
#include "../networking/discovery/domain/DiscoveredServer.h"
#include "../networking/messaging/infrastructure/JsonSerializer.h"

ServerController::ServerController(QObject *parent) : QObject(parent), m_broadcaster(
                                                          "Sundown Server", "server-uuid-1234",
                                                          static_cast<quint16>(50505)),
                                                      m_discoveryListener(static_cast<quint16>(50505))
{
    connect(&m_discoveryListener, &UdpDiscoveryListener::serverDiscovered, this, &ServerController::onServerDiscovered);
    connect(&m_tcpServer, &TcpServer::sessionCreated, this, &ServerController::onSessionCreated);
    // Ignore clang here. False positive
}

void ServerController::start()
{
    m_broadcaster.start();
    m_discoveryListener.start();
    m_tcpServer.listen(QHostAddress::Any, 60000);

    simulateDiscovery();
}

void ServerController::stop()
{
    m_broadcaster.stop();
    m_discoveryListener.stop();
}

void ServerController::onServerDiscovered(const DiscoveryPacket &packet)
{
    DiscoveredServer server;
    server.deviceId = packet.deviceId;
    server.deviceName = packet.deviceName;
    server.address = packet.senderAddress;
    server.port = packet.serverPort;
    server.lastSeen = QDateTime::currentDateTimeUtc();

    m_registry.updateFromDiscovery(server);

    qDebug() << server.port;
}

void ServerController::simulateDiscovery()
{
    DiscoveredServer testServer;
    testServer.deviceId = "testId";
    testServer.deviceName = "testDevice";
    testServer.address = QHostAddress("192.168.1.42");
    testServer.port = 50505;
    testServer.lastSeen = QDateTime::currentDateTimeUtc();

    m_registry.updateFromDiscovery(testServer);
}

const DiscoveredServerRegistry &ServerController::registry() const
{
    return m_registry;
}

void ServerController::handlePairingRequest(TcpSession *session, const ProtocolMessage &msg)
{
    Q_UNUSED(session)
    Q_UNUSED(msg)
    // TODO: implement pairing handshake
}

void ServerController::sendError(TcpSession *session, const QString &reason)
{
    ProtocolMessage err;
    err.type = ProtocolMessageType::Error;
    err.payload["message"] = reason;
    err.correlationId = QUuid::createUuid().toString();

    session->send(err);
}

void ServerController::onSessionCreated(TcpSession *session)

{
    ProtocolMessage snapshot;
    snapshot.type = ProtocolMessageType::StateSnapshot;
    snapshot.payload = JsonSerializer::serializeState(m_state);
    snapshot.correlationId = QUuid::createUuid().toString();

    session->send(snapshot);
}

void ServerController::onMessageReceived(TcpSession *session, const ProtocolMessage &msg)
{
    switch (msg.type)
    {
        case ProtocolMessageType::PairingRequest:
            handlePairingRequest(session, msg);
            break;
        default:
            sendError(session, "UNSUPPORTED MESSAGE");
    }
}
