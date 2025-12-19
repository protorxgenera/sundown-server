#pragma once
#include <QTimer>
#include <QUdpSocket>

class DiscoveryBroadcaster : public QObject
{
        Q_OBJECT

    public:
        explicit DiscoveryBroadcaster(QString serverName, QString serverId, qint16 serverPort,
                                      QObject *parent = nullptr);

        void start();

        void stop();

    private slots:
        void broadcast();

    private:
        void setupSocket();

        QUdpSocket m_socket;
        QTimer m_timer;

        QString m_serverName;
        QString m_serverId;
        quint16 m_serverPort;
};
