#pragma once

#include <QDateTime>

class IShutdownExecutor;
class ShutdownScheduler;

class Controller
{
    public:
        Controller(IShutdownExecutor& executor, ShutdownScheduler& scheduler);

        bool scheduleShutdown(const QDateTime& time);
        bool cancelShutdown();

        bool hasScheduleShutdown() const;
        QDateTime scheduledTime() const;

    private:
        IShutdownExecutor& m_executor;
        ShutdownScheduler& m_scheduler;

};
