// Copyright (c) 2019 All Rights Reserved WestBot

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _robotClient( this )
{
    ui->setupUi(this);

    _gameTimer.setInterval( 25 );

    connect(
    & _gameTimer,
    & QTimer::timeout,
    this,
    [ this ]()
    {
        _robot->move( _robot->pos().x() + 1, _robot->pos().y() );
    } );

    GLWidget *openGL = new GLWidget( this );
    openGL->move( 0, 0 );

    _robot = new Robot( this );
    _robot->move( 25, 90 );

    ui->robotConStatus->setPixmap(QPixmap::fromImage( QImage( ":/resources/con_nok.png" ) ) );

    connect(
        & _robotClient,
        & RobotClient::connected,
        this,
        [ this ]()
        {
            ui->robotConStatus->setPixmap(QPixmap::fromImage( QImage( ":/resources/con_ok.png" ) ) );
            ui->connectBtn->setText( "Disconnect" );
        } );

    connect(
        & _robotClient,
        & RobotClient::disconnected,
        this,
        [ this ]()
        {
            ui->connectBtn->setText( "Connect" );
            ui->robotConStatus->setPixmap(QPixmap::fromImage( QImage( ":/resources/con_nok.png" ) ) );
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

    _robotClient.connectTo( ui->hostTxt->text(), ui->portTxt->text().toInt( & ok, 10 ) );

    if( ! _robotClient.isConnected() )
    {
        qDebug() << "Failed to connect to Robot";
        return;
    }
}

void MainWindow::on_moveBtn_clicked()
{
    bool ok;
    //_robot->move( ui->xPos->text().toInt( & ok, 10 ), ui->yPos->text().toInt( & ok, 10 ) );
    _gameTimer.start();
}
