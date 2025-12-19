#include "TestShutdownExecutor.h"

bool TestShutdownExecutor::executeShutdownAt(const QDateTime &targetTime)
{
    m_shutdownCalled = true;
    m_targetTime = targetTime;
    return m_executeResult;
}

bool TestShutdownExecutor::cancelShutdown()
{
    m_cancelCalled = true;
    return true;
}

bool TestShutdownExecutor::shutdownRequested() const
{
    return m_shutdownCalled;
}

QDateTime TestShutdownExecutor::requestedTime() const
{
    return m_targetTime;
}

bool TestShutdownExecutor::cancelRequested() const
{
    return m_cancelCalled;
}

void TestShutdownExecutor::setExecuteResult(bool result)
{
    m_executeResult = result;
}








