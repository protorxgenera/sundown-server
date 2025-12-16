#pragma once

#include <QDateTime>

enum class ShutdownOrigin
{
    Local, Remote
};

struct ShutdownState
{
    bool active = false;
    QDateTime targetTime;
    ShutdownOrigin origin = ShutdownOrigin::Local;
};