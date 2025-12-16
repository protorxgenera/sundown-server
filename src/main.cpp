#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>

#include "app/Controller.h"
#include "domain/ShutdownScheduler.h"
#include "infrastructure/WindowsShutdownExecutor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    WindowsShutdownExecutor executor;
    ShutdownScheduler scheduler;
    QDateTime targetDate = QDateTime::currentDateTime().addSecs(3500);

    Controller controller = Controller(executor, scheduler);
    controller.scheduleShutdown(targetDate);

    qDebug() << "Has schedule shutdown?: " << controller.hasActiveShutdown();

    // this line doesn't return anything, which means that the date is not passed as a reference, doesn't reach the Schedule class
    qDebug() << "What is the scheduled time?: " << controller.currentShutdown().toString();

    return QApplication::exec();
}
