#pragma once
#include "../domain/IShutdownExecutor.h"

// no business logic
// simulates success or failure
// lets tests inspect interactions
// is deterministic
// cannot accidentally pass tests for wrong reasons

class TestShutdownExecutor : public IShutdownExecutor
{
    public:
        bool executeShutdownAt(const QDateTime &targetTime) override;

        bool cancelShutdown() override;

        bool shutdownRequested() const;

        QDateTime requestedTime() const;

        bool cancelRequested() const;

        void setExecuteResult(bool result);


    private:
        bool m_executeResult = true;
        bool m_shutdownCalled = false;
        bool m_cancelCalled = false;
        QDateTime m_targetTime;
};
