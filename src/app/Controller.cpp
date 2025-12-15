#include "Controller.h"

#include "../domain/IShutdownExecutor.h"
#include "../domain/ShutdownScheduler.h"

Controller::Controller(IShutdownExecutor &executor, ShutdownScheduler &scheduler) : m_executor(executor),
    m_scheduler(scheduler)
{
}

bool Controller::scheduleShutdown(const QDateTime &time)
{
    if (!m_scheduler.scheduleAt(time))
    {
        return false;
    }

    if (m_executor.scheduleShutdownAt(time))
    {
        m_scheduler.cancel();
        return false;
    }

    return true;
}

bool Controller::cancelShutdown()
{
    if (!m_executor.cancelShutdown())
    {
        return false;
    }

    m_scheduler.cancel();
    return true;
}

bool Controller::hasScheduleShutdown() const
{
    return m_scheduler.hasSchedule();
}

QDateTime Controller::scheduledTime() const
{
    return m_scheduler.scheduledTime();
}
