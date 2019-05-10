// Copyright (c) 2019 All Rights Reserved WestBot

#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "include/WestBot/mainwindow.h"
#include "ui_mainwindow.h"

#include "include/WestBot/Table.hpp"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , _robotClient( this )
{
    ui->setupUi( this );

    _gameTimer.setInterval( 25 );

    connect(
        & _gameTimer,
        & QTimer::timeout,
        this,
        [ this ]()
        {
            _robot->move( _robot->pos().x() + 1, _robot->pos().y() );
        } );

    WestBot::Table* table = new WestBot::Table( this );
    table->move( 0, 0 );

    _robot = new WestBot::Robot( this );
    _robot->move( 25, 90 );

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
