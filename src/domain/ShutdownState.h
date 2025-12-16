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

    static ShutdownState inactive()
    {
        return ShutdownState{};
    }

    static ShutdownState activeAt(const QDateTime& time, ShutdownOrigin origin)
    {
        ShutdownState state;
        state.active = true;
        state.targetTime = time;
        state.origin = origin;
        return state;
    }

};