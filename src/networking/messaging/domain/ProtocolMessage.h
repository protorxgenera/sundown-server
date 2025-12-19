#pragma once

#include <QJsonObject>

struct ProtocolMessage
{
    QString type;
    QJsonObject payload;
};