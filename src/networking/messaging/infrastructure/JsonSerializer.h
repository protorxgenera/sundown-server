#pragma once
#include <qbytearray.h>
#include <QJsonObject>

#include "../domain/ServerState.h"

struct ServerState;

class JsonSerializer
{
    public:
        static QJsonObject serializeState(const ServerState& state)
        {
            QJsonObject obj;
            obj["shutdownScheduled"] = state.shutdownScheduled;
            obj["shutdownTime"] = state.shutdownTime.toString(Qt::ISODate);

            return obj;
        }
};
