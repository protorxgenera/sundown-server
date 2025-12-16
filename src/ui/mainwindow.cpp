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

    ui->pushStatus->setStyleSheet("text-align:left;");
    ui->pushDevice->setStyleSheet("text-align:left;");

    connect(ui->btnSchedule, &QPushButton::clicked, this, &MainWindow::onScheduleClicked);
    connect(ui->btnAbort, &QPushButton::clicked, this, &MainWindow::onAbortClicked);
    connect(ui->pushStatus, &QPushButton::clicked, this, &MainWindow::onScheduleDetailsClicked);
    connect(ui->pushDevice, &QPushButton::clicked, this, &MainWindow::onDeviceDetailsClicked);

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

void MainWindow::onScheduleDetailsClicked()
{
    m_scheduleDetails = !m_scheduleDetails;
    updateStatus();
}

void MainWindow::onDeviceDetailsClicked()
{
    m_deviceDetails = !m_deviceDetails;
    updateStatus();
}

void MainWindow::updateStatus()
{
    const ShutdownState state = m_controller.currentShutdown();

    if (!state.active)
    {
        ui->pushStatus->setText("no shutdown scheduled");
        ui->pushDevice->setText("no device");
        ui->btnAbort->setDisabled(true);
    } else
    {
        if (m_scheduleDetails)
        {
            ui->pushStatus->setText(state.targetTime.toString(Qt::TextDate));
        } else
        {
            ui->pushStatus->setText(QString::number(QDateTime::currentDateTime().secsTo(state.targetTime)/60) + " minutes to shutdown");
        }

        if (m_deviceDetails)
        {
            ui->pushDevice->setText("self");
        } else
        {
            ui->pushDevice->setText("HP Omen 17");
        }

        ui->btnAbort->setDisabled(false);

    }
}
