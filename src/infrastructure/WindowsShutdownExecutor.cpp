#include "WindowsShutdownExecutor.h"

#include <QProcess>

bool WindowsShutdownExecutor::executeShutdownAt(const QDateTime &targetTime)
{
    qint64 seconds = QDateTime::currentDateTime().secsTo(targetTime);

    if (seconds < 0)
    {
        return false;
    }

    QStringList args;

    args << "-s" << "-t" << QString::number(seconds);

    return QProcess::startDetached("shutdown", args);
}

bool WindowsShutdownExecutor::cancelShutdown()
{
    return QProcess::startDetached("shutdown", {"-a"});
}
