//
// Created by Ben on 12/17/2025.
//

#ifndef SUNDOWN_SERVER_MAINWINDOW_H
#define SUNDOWN_SERVER_MAINWINDOW_H

#include <QMainWindow>
#include "../app/Controller.h"
#include "../domain/ShutdownState.h"


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

    private:
        Ui::MainWindow *ui;
        void updateStatus();
        Controller& m_controller;
};


#endif //SUNDOWN_SERVER_MAINWINDOW_H
