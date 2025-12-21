#include "TcpSession.h"

TcpSession::TcpSession(QTcpSocket *socket, QObject *parent) : QObject(parent), m_socket(socket)
{
    connect(m_socket, &QTcpSocket::readyRead,
            this, &TcpSession::onReadyRead);

    connect(m_socket, &QTcpSocket::disconnected, this, [this]()
    {
        emit disconnected(this);
    });
}

void TcpSession::onReadyRead()
{
    const auto data = m_socket->readAll();

    auto doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return;

    auto obj = doc.object();

    ProtocolMessage msg;
    msg.type = static_cast<ProtocolMessageType>(obj["type"].toInt());
    msg.payload = obj["payload"].toObject();
    msg.correlationId = obj["correlationId"].toString();

    if (!isAllowed(msg))
    {
        qWarning() << "Protocol violation";
        return;
    }

    advanceState(msg);
    emit messageReceived(this, msg);
}

bool TcpSession::isAllowed(const ProtocolMessage &msg) const
{
    switch (m_state)
    {
        case SessionState::Connected:
            return msg.type == ProtocolMessageType::PairingRequest;
        case SessionState::Pairing:
            return msg.type == ProtocolMessageType::PairingResponse;
        case SessionState::Paired:
            return true;
        default:
            return false;
    }
}

void TcpSession::advanceState(const ProtocolMessage &msg)
{
    if (m_state == SessionState::Connected && msg.type == ProtocolMessageType::PairingRequest)
    {
        m_state = SessionState::Pairing;
    } else if (m_state == SessionState::Pairing && msg.type == ProtocolMessageType::PairingResponse)
    {
        m_state = SessionState::Paired;
    }
}

void TcpSession::send(const ProtocolMessage &msg)
{
    QJsonObject obj;
    obj["type"] = static_cast<int>(msg.type);
    obj["payload"] = msg.payload;
    obj["correlationId"] = msg.correlationId;

    QJsonDocument doc(obj);
    m_socket->write(doc.toJson(QJsonDocument::Compact));
}

void TcpSession::onSocketDisconnected()
{
    emit disconnected(this);

    m_socket->deleteLater();
    deleteLater();
}
