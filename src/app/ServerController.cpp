#include "ServerController.h"
#include "../networking/discovery/domain/DiscoveredServer.h"
#include "../networking/session/messaging/infrastructure/JsonSerializer.h"

ServerController::ServerController(QObject *parent) : QObject(parent), m_broadcaster(
                                                          "Sundown Server", "server-uuid-1234",
                                                          static_cast<quint16>(50505)),
                                                      m_discoveryListener(static_cast<quint16>(50505))
{
}

void ServerController::start()
{
    connect(&m_discoveryListener, &UdpDiscoveryListener::serverDiscovered,
            this, &ServerController::onServerDiscovered);

    connect(&m_sessions, &SessionManager::sessionConnected, this, &ServerController::onSessionConnected);

    connect(&m_sessions, &SessionManager::sessionDisconnected, this, &ServerController::onSessionDisconnected);

    connect(&m_sessions, &SessionManager::protocolMessage, this, &ServerController::onProtocolMessage);

    m_broadcaster.start();
    m_discoveryListener.start();
    m_sessions.start(60000);
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
}

void ServerController::onSessionConnected(SessionId id)
{
    qDebug() << "Session connected: " << id;
}

void ServerController::onSessionDisconnected(SessionId id)
{
    qDebug() << "Session disconnected: " << id;
}

void ServerController::onProtocolMessage(SessionId id, const ProtocolMessage &msg)
{
    switch (msg.type)
    {
        case ProtocolMessageType::PairingRequest:
            handlePairingRequest(id, msg);
            break;
        default:
            sendError(id, "Unsupported message type");
            break;
    }
}

void ServerController::handlePairingRequest(SessionId id, const ProtocolMessage &msg)
{
    qDebug() << "Handling pairing request from session" << id;

    ProtocolMessage reply;
    reply.type = ProtocolMessageType::PairingAccepted;
    reply.correlationId = msg.correlationId;

    QJsonObject payload;
    payload["serverName"] = "Sundown Server";
    payload["paired"] = true;

    reply.payload = payload;
    m_sessions.send(id, reply);
}

void ServerController::sendError(SessionId id, const QString &reason)
{
    ProtocolMessage msg;
    msg.type = ProtocolMessageType::Error;
    msg.correlationId = QUuid::createUuid().toString();

    QJsonObject payload;
    payload["reason"] = reason;
    msg.payload = payload;

    m_sessions.send(id, msg);
}