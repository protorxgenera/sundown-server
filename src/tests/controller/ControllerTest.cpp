#include "ControllerTest.h"

#include "../../domain/ShutdownScheduler.h"

/** verifies only controller logic
 * - scheduler is updated
 * - executor is called
 * - correct time passed
 * - no OS calls
 * - no timing dependence
 */


void ControllerTest::scheduleShutdown_success()
{
    ShutdownScheduler scheduler;
    TestShutdownExecutor executor;
    Controller controller(executor, scheduler);

    QDateTime targetTime = QDateTime::currentDateTime().addSecs(3400);
    bool result = controller.scheduleShutdown(targetTime);

    QVERIFY(result);
    QVERIFY(controller.hasScheduleShutdown());
    QCOMPARE(controller.scheduledTime(), targetTime);
    QVERIFY(executor.shutdownRequested());
    QCOMPARE(executor.requestedTime(), targetTime);
}

void ControllerTest::scheduleShutdown_executorFails()
{
    ShutdownScheduler scheduler;
    TestShutdownExecutor executor;
    Controller controller(executor, scheduler);

    QDateTime targetTime = QDateTime::currentDateTime().addSecs(3400);
    bool result = controller.scheduleShutdown(targetTime);

    QVERIFY(!result);
    QVERIFY(!controller.hasScheduleShutdown());
    QVERIFY(executor.shutdownRequested());
}

void ControllerTest::cancelShutdown_clearsSchedule()
{
    ShutdownScheduler scheduler;
    TestShutdownExecutor executor;
    Controller controller(executor, scheduler);

    QDateTime targetTime = QDateTime::currentDateTime().addSecs(3400);
    QVERIFY(controller.scheduleShutdown(targetTime));

    bool result = controller.cancelShutdown();

    QVERIFY(result);
    QVERIFY(!controller.hasScheduleShutdown());
    QVERIFY(executor.cancelRequested());
}