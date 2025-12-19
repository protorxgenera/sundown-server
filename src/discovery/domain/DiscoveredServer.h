#pragma once
#include <QDateTime>
#include <qhostaddress.h>

struct DiscoveredServer
{
    QString deviceId;
    QString deviceName;
    QHostAddress address;
    quint16 port;
    QDateTime lastSeen;
};
