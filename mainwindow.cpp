#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "datamanager.h"

#include "QtMqtt/QMqttClient"
#include "QtMqtt/QMqttTopicFilter"

#include "logger.h"
#include "datamanager.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logger* log = new logger(this);
    log->setUI(ui->wLoggerBox, ui->wLoggerButton);

    dataManager* dm = new dataManager(this);
    dm->setLogger(log);
    dm->setUI(ui->hostLine, ui->portLine, ui->mqConnect);
}

MainWindow::~MainWindow()
{
    delete ui;
}
