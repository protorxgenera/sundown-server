#pragma once

#include <QDateTime>

class WindowsShutdownExecutor
{

    public:
        bool scheduleShutdownAt(const QDateTime& targetTime);
        bool cancelShutdown();

};
