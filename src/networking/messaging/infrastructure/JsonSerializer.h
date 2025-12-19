#pragma once
#include <qbytearray.h>
#include <QJsonObject>

#include "../domain/ServerState.h"

struct ServerState;

class JsonSerializer
{
    public:
        static QByteArray serializeState(const ServerState& state)
        {
            QJsonObject obj;
            obj["type"] = "state_snapshot";
            obj["shutdownScheduled"] = state.shutdownScheduled;
            obj["shutdownTime"] = state.shutdownTime.toString(Qt::ISODate);

            return QJsonDocument(obj).toJson(QJsonDocument::Compact);
        }
};
