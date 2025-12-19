#pragma once
#include "DiscoveredServer.h"

class DiscoveredServerRegistry : public QObject
{
        Q_OBJECT

    public:
        DiscoveredServerRegistry(QObject *parent = nullptr);

        void updateFromDiscovery(const DiscoveredServer &server);

        QList<DiscoveredServer> servers() const;

        void removeExpired(const QDateTime &now);

    signals:
        void serversChanged();

    private:
        QHash<QString, DiscoveredServer> m_servers; // key = deviceId
        int m_timeoutSeconds = 10;
};
