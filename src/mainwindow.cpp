// Copyright (c) 2019 All Rights Reserved WestBot

#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "include/WestBot/mainwindow.h"
#include "ui_mainwindow.h"

namespace
{
    const double COEFF_REDUC = 0.2;
    const double PUCK_R = 38.1;
}

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , _robotClient( new WestBot::ClientStuff( "localhost", 4242 ) )
    , _scene( nullptr )
{
    ui->setupUi( this );

    _updateTimer.setInterval( 150 );

    _scene = new QGraphicsScene();
    _scene->setSceneRect( 0, 0, 600, 400 );

    QImage image( ":/resources/table.png" );
    QPixmap item( QPixmap::fromImage( image ) );
    QPixmap scaled = item.scaled(QSize(600, 400));

    ui->gameView->setScene( _scene );
    ui->gameView->setBackgroundBrush( scaled );
    ui->gameView->setFixedSize( 600, 400 );

    _scene->setItemIndexMethod( QGraphicsScene::NoIndex );

    ui->robotConStatus->setPixmap(
        QPixmap::fromImage( QImage( ":/resources/con_nok.png" ) ) );

    // ================================== //

    // THIS IS WORKING
    QRectF rect(-30, -30,30,30);
    QBrush myBrush(Qt::yellow);

    QGraphicsRectItem *rob = new QGraphicsRectItem( rect );
        _scene->addItem(rob);
        rob->setPos(0, 0 );
        rob->setBrush(myBrush);


   // THIS IS NOT !!!
   /* WestBot::Robot* rob = new WestBot::Robot( 0 );
    _scene->addItem(rob);
    rob->setPos(0, 0 );
    */

    connect(
        _robotClient,
        & WestBot::ClientStuff::hasReadSome,
        this,
        [ this, rob ]( WestBot::SimData data )
        {
            qDebug() << "RCV SOMETHING" << data.objectPos.x << data.objectPos.y;
            rob->setPos( data.objectPos.x, data.objectPos.y  );
        } );

    // ================================== //

    connect(
        _robotClient,
        & WestBot::ClientStuff::statusChanged,
        this,
        [ this ]( bool status )
        {
            if( status )
            {
                ui->robotConStatus->setPixmap(
                    QPixmap::fromImage( QImage( ":/resources/con_ok.png" ) ) );
                ui->connectBtn->setText( "Disconnect" );
            }
            else
            {
                ui->connectBtn->setText( "Connect" );
                ui->robotConStatus->setPixmap(
                    QPixmap::fromImage( QImage( ":/resources/con_nok.png" ) ) );
            }
        } );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectBtn_clicked()
{
    bool ok;
    if( _robotClient->getStatus() )
    {
        _robotClient->closeConnection();
        return;
    }

    _robotClient->connect2host();
}

void MainWindow::on_moveBtn_clicked()
{
    // TODO: XXX
}
