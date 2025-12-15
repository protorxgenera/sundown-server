#pragma once

#include <QDateTime>

// Represents the current shutdown schedule state. Simple struct. No behavior

struct ShutdownSchedule
{
    bool active = false;
    QDateTime targetTime;
};