#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>

#include "domain/ShutdownSchedule.h"
#include "domain/ShutdownScheduler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    ShutdownScheduler scheduler;

    QDateTime shutdownTime = QDateTime::currentDateTime().addSecs(3600);
    scheduler.scheduleAt(shutdownTime);

    ShutdownSchedule schedule = scheduler.currentSchedule();

    qDebug() << "Active: " << schedule.active;
    qDebug() << "Shutdown at: " << schedule.targetTime.toString();

    scheduler.cancel();

    qDebug() << "After cancel, active: " << scheduler.currentSchedule().active;
    qDebug() << "After cancel, target time: " << scheduler.currentSchedule().targetTime.toString();

    return QApplication::exec();
}
