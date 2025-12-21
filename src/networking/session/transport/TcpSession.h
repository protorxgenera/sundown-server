#pragma once
#include <QTcpSocket>
#include "../messaging/domain/ProtocolMessage.h"
#include "../domain/SessionState.h"

/**
 * Responsibility: convert QTcpSocket -> JSON document -> ProtocolMessage
 *
 * Owns: protocol rules, validation, and state transitions.
 */

class TcpSession : public QObject
{
        Q_OBJECT

    public:
        explicit TcpSession(QTcpSocket *socket, QObject *parent = nullptr);

        void send(const ProtocolMessage &msg);

        SessionState state() const { return m_state; };

    signals:
        void messageReceived(TcpSession *session, const ProtocolMessage &msg);
        void disconnected(TcpSession *session);

    public slots:
        void onReadyRead();
        void onSocketDisconnected();

    private:
        bool isAllowed(const ProtocolMessage& msg) const;
        void advanceState(const ProtocolMessage& msg);

        QTcpSocket *m_socket;
        SessionState m_state = SessionState::Connected;
};
