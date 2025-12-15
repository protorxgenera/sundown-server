#pragma once

#include "ShutdownSchedule.h"
#include <QDateTime>

// Manages the scheduling logic. Doesn't perform the shutdown.

class ShutdownScheduler
{

    public:
        ShutdownScheduler();

        void scheduleAt(const QDateTime& time);
        void cancel();

        ShutdownSchedule currentSchedule() const;

    private:
        ShutdownSchedule m_schedule;

};

