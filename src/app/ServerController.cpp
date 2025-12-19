#include "ServerController.h"
#include "../discovery/domain/DiscoveredServer.h"

ServerController::ServerController(QObject *parent) : QObject(parent), m_broadcaster(
                                                          "Sundown Server", "server-uuid-1234",
                                                          static_cast<quint16>(50505)), m_discoveryListener(static_cast<quint16>(50505))
{
    connect(&m_discoveryListener, &UdpDiscoveryListener::serverDiscovered, this, &ServerController::onServerDiscovered);
}

void ServerController::start()
{
    m_broadcaster.start();
    m_discoveryListener.start();
    simulateDiscovery();
}

void ServerController::stop()
{
    m_broadcaster.stop();
    m_discoveryListener.stop();
}

void ServerController::onServerDiscovered(const DiscoveryPacket& packet)
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

const DiscoveredServerRegistry& ServerController::registry() const
{
    return m_registry;
}