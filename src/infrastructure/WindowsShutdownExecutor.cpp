#include "WindowsShutdownExecutor.h"

#include <QProcess>

bool WindowsShutdownExecutor::scheduleShutdownAt(const QDateTime &targetTime)
{
    qint64 seconds = QDateTime::currentDateTime().secsTo(targetTime);

    if (seconds < 0)
    {
        return false;
    }

    return QProcess::startDetached("shutdown", {"-s", "-t", QString::number(seconds)});
}

bool WindowsShutdownExecutor::cancelShutdown()
{
    return QProcess::startDetached("shutdown", {"-a"});
}
