#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>

#include "app/Controller.h"
#include "app/ServerController.h"
#include "shutdown/domain/ShutdownScheduler.h"
#include "shutdown/infrastructure/FileShutdownStateRepository.h"
#include "shutdown/infrastructure/InMemoryShutdownStateRepository.h"
#include "shutdown/infrastructure/WindowsShutdownExecutor.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("PROTORXGENERA");
    QCoreApplication::setApplicationName("Sundown Server");

    ServerController server;
    server.start();

    WindowsShutdownExecutor executor;

    FileShutdownStateRepository stateRepository;
    ShutdownScheduler scheduler(stateRepository);

    Controller controller = Controller(executor, scheduler);

    MainWindow window(controller);
    window.show();


    return QApplication::exec();
}
