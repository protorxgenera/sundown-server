#include "UdpDiscoveryListener.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonparseerror.h>

UdpDiscoveryListener::UdpDiscoveryListener(quint16 listenPort, QObject *parent) : IDiscoveryListener(parent),
    m_listenPort(listenPort)
{
}

void UdpDiscoveryListener::start()
{
    m_socket.bind(QHostAddress::AnyIPv4, m_listenPort, QUdpSocket::ShareAddress);
    connect(&m_socket, &QUdpSocket::readyRead, this, &UdpDiscoveryListener::onReadyRead);
}

void UdpDiscoveryListener::stop()
{
    m_socket.close();
}

void UdpDiscoveryListener::onReadyRead()
{
    while (m_socket.hasPendingDatagrams())
    {
        // Flow:
        // Socket → QByteArray → QJson → DiscoveryPacket → signal

        QByteArray datagram;
        datagram.resize(static_cast<int>(m_socket.pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        m_socket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(datagram, &error);

        if (error.error != QJsonParseError::NoError || !doc.isObject())
        {
            continue;
        }

        QJsonObject obj = doc.object();

        DiscoveryPacket packet;
        packet.deviceId = obj["deviceId"].toString();
        packet.deviceName = obj["deviceName"].toString();
        packet.serverPort = obj["serverPort"].toInt();
        packet.senderAddress = sender;

        emit serverDiscovered(packet);
    }
}
