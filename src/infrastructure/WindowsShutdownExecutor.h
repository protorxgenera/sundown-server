#pragma once

#include <QDateTime>

#include "../domain/IShutdownExecutor.h"

class WindowsShutdownExecutor : public IShutdownExecutor
{

    public:
        bool scheduleShutdownAt(const QDateTime& time) override;
        bool cancelShutdown() override;

};
