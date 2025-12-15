#pragma once

#include <QDateTime>

class IShutdownExecutor
{
    public:
        virtual ~IShutdownExecutor() = default;

        virtual bool scheduleShutdownAt(const QDateTime& time) = 0;
        virtual bool cancelShutdown() = 0;
};
