#pragma once

#include <QDateTime>

#include "ShutdownState.h"

// Manages the scheduling logic. Doesn't perform the shutdown.

class ShutdownScheduler
{
    public:
        ShutdownScheduler();

        bool scheduleAt(const QDateTime &time, ShutdownOrigin origin = ShutdownOrigin::Local);

        void cancel();

        bool hasActiveShutdown() const;

        ShutdownState currentState() const;


    private:
        ShutdownState m_state;
};
