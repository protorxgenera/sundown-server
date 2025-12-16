#pragma once

#include <QDateTime>

class IShutdownExecutor;
class ShutdownScheduler;
class ShutdownState;

class Controller
{
    public:
        Controller(IShutdownExecutor& executor, ShutdownScheduler& scheduler);

        bool scheduleShutdown(const QDateTime& time);
        bool cancelShutdown();

        bool hasActiveShutdown() const;
        ShutdownState currentShutdown() const;

    private:
        IShutdownExecutor& m_executor;
        ShutdownScheduler& m_scheduler;

};
