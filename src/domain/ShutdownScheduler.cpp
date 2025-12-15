#include "ShutdownScheduler.h"

ShutdownScheduler::ShutdownScheduler() : m_active(false)
{
}

bool ShutdownScheduler::scheduleAt(const QDateTime &time)
{
    if (!time.isValid() || time <= QDateTime::currentDateTime())
    {
        return false;
    }
    m_active = true;
    m_targetTime = time;

    return true;
}

void ShutdownScheduler::cancel()
{
    m_active = false;
    m_targetTime = QDateTime();
}

bool ShutdownScheduler::hasSchedule() const
{
    return m_active;
}

QDateTime ShutdownScheduler::scheduledTime() const
{
    return m_targetTime;
}