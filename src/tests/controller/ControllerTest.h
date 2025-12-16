#pragma once

#include <QtTest/QtTest>
#include <QDateTime>
#include "../../app/Controller.h"
#include "../../domain/ShutdownScheduler.h"
#include "../../infrastructure/TestShutdownExecutor.h"

class ControllerTest : public QObject
{
        Q_OBJECT

    private slots:
        void scheduleShutdown_success();

        void scheduleShutdown_executorFails();

        void cancelShutdown_clearsSchedule();
};
