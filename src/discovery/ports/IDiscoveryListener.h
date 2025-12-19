#pragma once

#include "../infrastructure/DiscoveryPacket.h"

class IDiscoveryListener : public QObject
{
        Q_OBJECT

    public:
        explicit IDiscoveryListener(QObject *parent = nullptr) : QObject(parent) {};

        virtual ~IDiscoveryListener() = default;

        virtual void start() = 0;

        virtual void stop() = 0;

    signals:
        void serverDiscovered(const DiscoveryPacket& packet);
};
