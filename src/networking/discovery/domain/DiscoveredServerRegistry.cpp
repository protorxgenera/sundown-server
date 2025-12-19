#include "DiscoveredServerRegistry.h"

DiscoveredServerRegistry::DiscoveredServerRegistry(QObject *parent) : QObject(parent)
{
}

void DiscoveredServerRegistry::updateFromDiscovery(const DiscoveredServer &server)
{
    bool changed = false;

    if (!m_servers.contains(server.deviceId))
    {
        m_servers.insert(server.deviceId, server);
    } else
    {
        m_servers[server.deviceId] = server;
        changed = true;
    }

    if (changed)
    {
        emit serversChanged();
    }
}

QList<DiscoveredServer> DiscoveredServerRegistry::servers() const
{
    return m_servers.values();
}

void DiscoveredServerRegistry::removeExpired(const QDateTime &now)
{
    bool changed = false;

    for (auto it = m_servers.begin(); it != m_servers.end();)
    {
        if (it->lastSeen.secsTo(now) > m_timeoutSeconds)
        {
            it = m_servers.erase(it);
            changed = true;
        } else
        {
            it++;
        }
    }

    if (changed)
    {
        emit serversChanged();
    }
}
