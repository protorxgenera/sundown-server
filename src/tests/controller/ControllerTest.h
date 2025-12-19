#pragma once

#include <QtTest/QtTest>
#include <QDateTime>
#include "../../app/Controller.h"
#include "../../shutdown/domain/ShutdownScheduler.h"
#include "../../shutdown/tests/TestShutdownExecutor.h"

class ControllerTest : public QObject
{
        Q_OBJECT

    private slots:
        void scheduleShutdown_success();

        void scheduleShutdown_executorFails();

        void cancelShutdown_clearsSchedule();
};
