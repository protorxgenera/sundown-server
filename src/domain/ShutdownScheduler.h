#pragma once

#include <QDateTime>

#include "IShutdownStateRepository.h"
#include "ShutdownState.h"

// Manages the scheduling logic. Doesn't perform the shutdown.

class ShutdownScheduler
{
    public:
        ShutdownScheduler(IShutdownStateRepository& repository);

        bool scheduleAt(const QDateTime &time, ShutdownOrigin origin = ShutdownOrigin::Local);

        void cancel();

        bool hasActiveShutdown() const;

        ShutdownState currentState() const;


    private:
        ShutdownState m_state;
        IShutdownStateRepository& m_repository;
};
