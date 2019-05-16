// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHash>
#include <QMainWindow>
#include <QGraphicsScene>

#include "Puck.hpp"
#include "Robot.hpp"
#include "clientstuff.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

signals:
    void updateMap();

private slots:
    void on_connectBtn_clicked();

    void on_moveBtn_clicked();

    void on_startBtn_clicked();

    void on_pushButton_6_clicked();

private:
    //WestBot::RobotTcpClient _robotClient;
    WestBot::ClientStuff* _robotClient;
    QGraphicsScene* _scene;
    QHash< uint8_t, WestBot::Robot::Ptr > _robots;
    QHash< uint8_t, WestBot::Puck::Ptr > _pucks;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
