#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>

#include "domain/ShutdownSchedule.h"
#include "domain/ShutdownScheduler.h"
#include "infrastructure/WindowsShutdownExecutor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    // test 1: scheduler

    ShutdownScheduler scheduler1;

    QDateTime shutdownTime = QDateTime::currentDateTime().addSecs(3600);
    scheduler1.scheduleAt(shutdownTime);

    ShutdownSchedule schedule = scheduler1.currentSchedule();

    qDebug() << "Active: " << schedule.active;
    qDebug() << "Shutdown at: " << schedule.targetTime.toString();

    scheduler1.cancel();

    qDebug() << "After cancel, active: " << scheduler1.currentSchedule().active;
    qDebug() << "After cancel, target time: " << scheduler1.currentSchedule().targetTime.toString();

    // test 2: executor

    ShutdownScheduler scheduler2;
    WindowsShutdownExecutor executor;

    QDateTime shutdownTime2 = QDateTime::currentDateTime().addSecs(3600);
    scheduler2.scheduleAt(shutdownTime2);

    if (executor.scheduleShutdownAt(shutdownTime2))
    {
        qDebug() << "Shutdown scheduled";
    } else
    {
        qDebug() << "Failed to schedule shutdown";
    }

    return QApplication::exec();
}
