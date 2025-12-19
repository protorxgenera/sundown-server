//
// Created by Ben on 12/17/2025.
//

#ifndef SUNDOWN_SERVER_MAINWINDOW_H
#define SUNDOWN_SERVER_MAINWINDOW_H

#include <QMainWindow>
#include "../app/Controller.h"
#include "../shutdown/domain/ShutdownState.h"


QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(Controller &controller, QWidget *parent = nullptr);

        ~MainWindow() override;

    private slots:
        void onScheduleClicked();
        void onAbortClicked();
        void onScheduleDetailsClicked();
        void onDeviceDetailsClicked();

    private:
        Ui::MainWindow *ui;
        Controller& m_controller;

        bool m_scheduleDetails = false;
        bool m_deviceDetails = false;

        void updateStatus();
};


#endif //SUNDOWN_SERVER_MAINWINDOW_H
