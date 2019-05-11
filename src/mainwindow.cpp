// Copyright (c) 2019 All Rights Reserved WestBot

#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "include/WestBot/mainwindow.h"
#include "ui_mainwindow.h"

#include "include/WestBot/Puck.hpp"
#include "include/WestBot/Table.hpp"
#include "include/WestBot/Robot.hpp"

namespace
{
    const double COEFF_REDUC = 0.2;
    const double PUCK_R = 38.1;
}

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , _robotClient( this )
{
    ui->setupUi( this );

    _gameTimer.setInterval( 25 );

    static int ang = 0;
    connect(
        & _gameTimer,
        & QTimer::timeout,
        this,
        [ this ]()
        {
            _robot->move( _robot->pos().x() + 1, _robot->pos().y() );
            //_robot->setZRotation( ang+=10 );
        } );

    WestBot::Table* table = new WestBot::Table( this );
    table->move( 0, 0 );

    _robot = new WestBot::Robot( this );
    _robot->show();

    //_robot->move( 25, 90 );

    WestBot::Puck* red1;
    red1 = new WestBot::Puck( this, 0 );
    red1->setPosition(
        ( 500.0 - PUCK_R ) * COEFF_REDUC,
        ( 450.0 - PUCK_R ) * COEFF_REDUC );

    WestBot::Puck* green1;
    green1 = new WestBot::Puck( this, 1 );
    green1->setPosition(
        ( 500.0 - PUCK_R ) * COEFF_REDUC,
        ( 1050.0 - PUCK_R ) * COEFF_REDUC );

    ui->robotConStatus->setPixmap(
        QPixmap::fromImage( QImage( ":/resources/con_nok.png" ) ) );

    connect(
        & _robotClient,
        & WestBot::RobotTcpClient::connected,
        this,
        [ this ]()
        {
            ui->robotConStatus->setPixmap(
                QPixmap::fromImage( QImage( ":/resources/con_ok.png" ) ) );
            ui->connectBtn->setText( "Disconnect" );
        } );

    connect(
        & _robotClient,
        & WestBot::RobotTcpClient::disconnected,
        this,
        [ this ]()
        {
            ui->connectBtn->setText( "Connect" );
            ui->robotConStatus->setPixmap(
                QPixmap::fromImage( QImage( ":/resources/con_nok.png" ) ) );
        } );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectBtn_clicked()
{
    bool ok;
    if( _robotClient.isConnected() )
    {
        _robotClient.disconnectFrom();
        return;
    }

    _robotClient.connectTo(
        ui->hostTxt->text(),
        ui->portTxt->text().toInt( & ok, 10 ) );

    if( ! _robotClient.isConnected() )
    {
        qDebug() << "Failed to connect to Robot";
        return;
    }
}

void MainWindow::on_moveBtn_clicked()
{
    bool ok;
    _gameTimer.start();
}
