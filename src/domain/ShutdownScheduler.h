#pragma once

#include <QDateTime>

// Manages the scheduling logic. Doesn't perform the shutdown.

class ShutdownScheduler
{

    public:
        ShutdownScheduler();

        bool scheduleAt(const QDateTime& time);
        void cancel();

        bool hasSchedule() const;
        QDateTime scheduledTime() const;


    private:
        bool m_active;
        QDateTime m_targetTime;


};

