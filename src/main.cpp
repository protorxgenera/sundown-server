#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>

#include "app/Controller.h"
#include "domain/ShutdownScheduler.h"
#include "infrastructure/FileShutdownStateRepository.h"
#include "infrastructure/InMemoryShutdownStateRepository.h"
#include "infrastructure/WindowsShutdownExecutor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("PROTORXGENERA");
    QCoreApplication::setApplicationName("Sundown Server");

    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    WindowsShutdownExecutor executor;

    FileShutdownStateRepository stateRepository;
    ShutdownScheduler scheduler(stateRepository);
    QDateTime targetDate = QDateTime::currentDateTime().addSecs(3500);

    Controller controller = Controller(executor, scheduler);
    controller.scheduleShutdown(targetDate);

    qDebug() << "Has schedule shutdown?: " << controller.hasActiveShutdown();

    // this line doesn't return anything, which means that the date is not passed as a reference, doesn't reach the Schedule class
    qDebug() << "What is the scheduled time?: ";

    return QApplication::exec();
}
