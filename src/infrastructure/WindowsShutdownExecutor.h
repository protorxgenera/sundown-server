#pragma once

#include <QDateTime>

#include "../domain/IShutdownExecutor.h"

class WindowsShutdownExecutor : public IShutdownExecutor
{

    public:
        bool executeShutdownAt(const QDateTime& time) override;
        bool cancelShutdown() override;

};
