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
    m_sessions.clear();
}

void SessionManager::send(SessionId id, const ProtocolMessage &msg)
{
    auto it = m_sessions.find(id);
    if (it == m_sessions.end()) return;

    it.value().session->send(msg);
}

void SessionManager::onSessionCreated(TcpSession *session)
{
    SessionId id = QUuid::createUuid();

    m_sessions.insert(id, SessionEntry{
        .session = session,
        .state = SessionState::Connected
    });

    connect(session, &TcpSession::messageReceived,
            this, [this, id](TcpSession *session, const ProtocolMessage &msg)
            {
                auto it = m_sessions.find(id);
                if (it == m_sessions.end())
                    return;

                onSessionMessage(it.value().session, msg);
            });

    connect(session, &TcpSession::disconnected,
            this, [this, id]()
            {
                auto it = m_sessions.find(id);
                if (it == m_sessions.end())
                    return;

                onSessionDisconnected(it->session);
            });

    emit sessionConnected(id);
}

void SessionManager::onSessionDisconnected(TcpSession *session)
{
    auto it = std::ranges::find_if(m_sessions, [session](const SessionEntry &e) { return e.session == session; });

    if (it == m_sessions.end()) return;

    SessionId id = it.key();
    m_sessions.erase(it);

    emit sessionDisconnected(id);
}

void SessionManager::onSessionMessage(TcpSession *session, const ProtocolMessage &msg)
{
    auto it = std::ranges::find_if(m_sessions,
                                   [session](const SessionEntry &e)
                                   {
                                       return e.session == session;
                                   });

    if (it == m_sessions.end())
        return;

    SessionId id = it.key();
    SessionState state = it->state;

    // state-based validation
    if (state == SessionState::Connected &&
        msg.type != ProtocolMessageType::PairingRequest)
    {
        return; // silently drop or error
    }

    emit protocolMessage(id, msg);
}
