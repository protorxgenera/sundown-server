//
// Created by Ben on 12/17/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(Controller &controller, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
                                                                  m_controller(controller)
{
    ui->setupUi(this);

    connect(ui->btnSchedule, &QPushButton::clicked, this, &MainWindow::onScheduleClicked);
    connect(ui->btnAbort, &QPushButton::clicked, this, &MainWindow::onAbortClicked);

    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onScheduleClicked()
{
    int hours = ui->fieldHours->value() * 3600;
    int minutes = ui->fieldMinutes->value() * 60;
    int seconds = hours + minutes;

    m_controller.scheduleShutdown(QDateTime::currentDateTime().addSecs(seconds));

    updateStatus();
}

void MainWindow::onAbortClicked()
{
    m_controller.cancelShutdown();
    updateStatus();
}

void MainWindow::updateStatus()
{
    const ShutdownState state = m_controller.currentShutdown();

    if (!state.active)
    {
        ui->labelStatus->setText("no shutdown scheduled");
        ui->labelDevice->setText("no device");
        ui->btnAbort->setDisabled(true);
    } else
    {
        ui->labelStatus->setText(state.targetTime.toString(Qt::TextDate));
        ui->labelDevice->setText("self");
        ui->btnAbort->setDisabled(false);
    }
}
