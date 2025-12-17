#include "DiscoveryBroadcaster.h"

#include <qjsonobject.h>
#include <QVariant>

static constexpr int BROADCAST_INTERVAL_MS = 2000;
static constexpr quint16 DISCOVERY_PORT = 45453;


DiscoveryBroadcaster::DiscoveryBroadcaster(QString serverName, QString serverId, qint16 serverPort,
                                           QObject *parent) : QObject(parent), m_serverName(serverName),
                                                              m_serverId(serverId), m_serverPort(serverPort)
{
    setupSocket();

    connect(&m_timer, &QTimer::timeout, this, &DiscoveryBroadcaster::broadcast);
}

void DiscoveryBroadcaster::start()
{
    if (m_timer.isActive())
    {
        return;
    }

    m_timer.start(BROADCAST_INTERVAL_MS);
    broadcast();
}

void DiscoveryBroadcaster::stop()
{
    m_timer.stop();
}

void DiscoveryBroadcaster::setupSocket()
{
    m_socket.setSocketOption(QAbstractSocket::MulticastTtlOption, QVariant(1));
}

void DiscoveryBroadcaster::broadcast()
{
    QJsonObject payload;

    payload["type"] = "SUNDOWN_DISCOVERY";
    payload["version"] = 1;
    payload["serverName"] = m_serverName;
    payload["serverId"] = m_serverId;
    payload["port"] = static_cast<int>(m_serverPort);

    QJsonDocument doc(payload);
    QByteArray datagram = doc.toJson(QJsonDocument::Compact);

    m_socket.writeDatagram(datagram, QHostAddress::Broadcast, DISCOVERY_PORT);

    qDebug() << "broadcasting...";
}