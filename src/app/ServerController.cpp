#include "ServerController.h"

ServerController::ServerController(QObject *parent) : QObject(parent), m_broadcaster(
                                                          "Sundown Server", "server-uuid-1234",
                                                          static_cast<quint16>(50505))
{
}

void ServerController::start()
{
    m_broadcaster.start();
}

void ServerController::stop()
{
    m_broadcaster.stop();
}
