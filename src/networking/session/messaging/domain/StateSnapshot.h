#pragma once

#include <QDateTime>

struct StateSnapshot
{
    bool shutdownScheduled = false;
    QDateTime shutdownTime;
};