#include "Controller.h"

#include "../shutdown/ports/IShutdownExecutor.h"
#include "../shutdown/domain/ShutdownScheduler.h"

Controller::Controller(IShutdownExecutor &executor, ShutdownScheduler &scheduler) : m_executor(executor),
    m_scheduler(scheduler)
{
}

bool Controller::scheduleShutdown(const QDateTime &targetTime)
{
    if (m_scheduler.hasActiveShutdown())
    {
        m_executor.cancelShutdown();
    }

    if (!m_scheduler.scheduleAt(targetTime))
    {
        return false;
    }

    if (!m_executor.executeShutdownAt(targetTime))
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

bool Controller::hasActiveShutdown() const
{
    return m_scheduler.hasActiveShutdown();
}

ShutdownState Controller::currentShutdown() const
{
    return m_scheduler.currentState();
}
