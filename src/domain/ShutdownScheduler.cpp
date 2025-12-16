#include "ShutdownScheduler.h"

ShutdownScheduler::ShutdownScheduler()
{
    m_state.active = false;
}

bool ShutdownScheduler::scheduleAt(const QDateTime &time, ShutdownOrigin origin)
{
    if (!time.isValid() || time <= QDateTime::currentDateTime())
    {
        return false;
    }
    m_state.active = true;
    m_state.targetTime = time;
    m_state.origin = origin;

    return true;
}

void ShutdownScheduler::cancel()
{
    m_state = ShutdownState{};
}

bool ShutdownScheduler::hasActiveShutdown() const
{
    return m_state.active;
}

ShutdownState ShutdownScheduler::currentState() const
{
    return m_state;
}

