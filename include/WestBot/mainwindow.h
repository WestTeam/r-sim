// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

#include "RobotTcpClient.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

private slots:
    void on_connectBtn_clicked();

    void on_moveBtn_clicked();

private:
    WestBot::RobotTcpClient _robotClient;
    QGraphicsScene* _scene;
    QTimer _gameTimer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
