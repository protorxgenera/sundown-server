#include "ShutdownScheduler.h"

ShutdownScheduler::ShutdownScheduler()
{
    m_schedule.active = false;
}

void ShutdownScheduler::scheduleAt(const QDateTime &time)
{
    m_schedule.active = true;
    m_schedule.targetTime = time;
}

void ShutdownScheduler::cancel()
{
    m_schedule.active = false;
    m_schedule.targetTime = QDateTime();
}

ShutdownSchedule ShutdownScheduler::currentSchedule() const
{
    return m_schedule;
}


