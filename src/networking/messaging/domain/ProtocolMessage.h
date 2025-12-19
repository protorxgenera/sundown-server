#pragma once

#include <QJsonObject>
#include "ProtocolMessageType.h"

struct ProtocolMessage
{
    ProtocolMessageType type;
    QJsonObject payload;
    QString correlationId; // enables request/response tracking
};