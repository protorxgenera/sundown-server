#pragma once

#include <QDateTime>

struct ServerState
{
    bool shutdownScheduled = false;
    QDateTime shutdownTime;
};