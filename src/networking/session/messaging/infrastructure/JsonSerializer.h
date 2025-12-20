#pragma once
#include <qbytearray.h>
#include <QJsonObject>

#include "../domain/StateSnapshot.h"

struct StateSnapshot;

class JsonSerializer
{
    public:
        static QJsonObject serializeState(const StateSnapshot& state)
        {
            QJsonObject obj;
            obj["shutdownScheduled"] = state.shutdownScheduled;
            obj["shutdownTime"] = state.shutdownTime.toString(Qt::ISODate);

            return obj;
        }
};
