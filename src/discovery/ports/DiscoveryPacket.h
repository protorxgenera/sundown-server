#pragma once
#include <qhostaddress.h>

struct DiscoveryPacket
{
    QString deviceId;
    QString deviceName;
    quint16 serverPort;

    QHostAddress senderAddress;
};
