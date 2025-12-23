#include "SessionManager.h"


SessionManager::SessionManager(QObject *parent) : QObject(parent)
{
    connect(&m_server, &TcpServer::sessionCreated, this, &SessionManager::onSessionCreated);
    // clang false positive
}

void SessionManager::start(quint16 port)
{
    m_server.start(port);
}

void SessionManager::stop()
{
    m_server.stop();

    for (auto session: m_sessions)
    {
        session->deleteLater();
    }

    m_sessions.clear();
}

void SessionManager::send(SessionId id, const ProtocolMessage &msg)
{
    if (!m_sessions.contains(id)) return;

    m_sessions[id]->send(msg);
}

void SessionManager::onSessionCreated(TcpSession *session)
{
    SessionId id = QUuid::createUuid();

    m_sessions.insert(id, session);

    connect(session, &TcpSession::messageReceived,
            this, [this, id](TcpSession *session, const ProtocolMessage &msg)
            {
                emit protocolMessage(id, msg);
            });

    connect(session, &TcpSession::disconnected,
            this, [this, id]()
            {
                auto session = m_sessions.take(id);
                session->deleteLater();

                emit sessionDisconnected(id);
            });

    emit sessionConnected(id);
}
