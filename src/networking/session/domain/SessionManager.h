#pragma once

#include "SessionId.h"
#include "../messaging/domain/ProtocolMessage.h"
#include "../transport/TcpSession.h"
#include "../transport/TcpServer.h"
#include <QTcpServer>

/**
 * The sole responsibility: SessionManager owns the lifecycle of TcpSession objects
 *
 * This means:
 * - keeping track of active sessions
 * - routing messages upward (to ServerController or domain logic)
 * - cleaning up when sessions disappear
 *
 * Owns: session lifecycle and routing by SessionId.
 */

class SessionManager : public QObject
{
        Q_OBJECT

    public:
        explicit SessionManager(QObject *parent = nullptr);

        void start(quint16 port);

        void stop();

        void send(SessionId id, const ProtocolMessage &msg);

    signals:
        void sessionConnected(SessionId id);

        void sessionDisconnected(SessionId id);

        void protocolMessage(SessionId id, const ProtocolMessage &msg);

    private slots:
        void onSessionCreated(TcpSession *session);

        void onSessionDisconnected(TcpSession *session);

        void onSessionMessage(TcpSession *session, const ProtocolMessage &msg);

    private:
        struct SessionEntry
        {
            TcpSession *session = nullptr;
            SessionState state = SessionState::Connected;
        };

        TcpServer m_server;
        QHash<SessionId, SessionEntry> m_sessions;
};
