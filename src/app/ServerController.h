#pragma once
#include "../infrastructure/network/discovery/DiscoveryBroadcaster.h"

class ServerController : public QObject
{
        Q_OBJECT

    public:
        explicit ServerController(QObject* parent = nullptr);

        void start();

        void stop();

    private:
        DiscoveryBroadcaster m_broadcaster;
};
