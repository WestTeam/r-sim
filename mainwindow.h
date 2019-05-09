// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "robotclient.h"
#include <robot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectBtn_clicked();

    void on_moveBtn_clicked();

private:
    Ui::MainWindow *ui;
    RobotClient _robotClient;
    Robot* _robot;
    QTimer _gameTimer;
};

#endif // MAINWINDOW_H
