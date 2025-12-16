#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>

#include "app/Controller.h"
#include "domain/ShutdownScheduler.h"
#include "infrastructure/FileShutdownStateRepository.h"
#include "infrastructure/InMemoryShutdownStateRepository.h"
#include "infrastructure/WindowsShutdownExecutor.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("PROTORXGENERA");
    QCoreApplication::setApplicationName("Sundown Server");

    WindowsShutdownExecutor executor;

    FileShutdownStateRepository stateRepository;
    ShutdownScheduler scheduler(stateRepository);

    Controller controller = Controller(executor, scheduler);

    MainWindow window(controller);
    window.show();


    return QApplication::exec();
}
