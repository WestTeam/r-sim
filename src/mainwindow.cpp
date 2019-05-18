// Copyright (c) 2019 All Rights Reserved WestBot

#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "include/WestBot/mainwindow.h"
#include "ui_mainwindow.h"

#define M_PI 3.1415

#define DEG(x) ((x) * (180.0 / M_PI))
#define RAD(x) ((x) * M_PI / 180.0)

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

    connect(
        _robotClient,
        & WestBot::ClientStuff::hasReadSome,
        this,
        [ this ]( WestBot::SimData data )
        {
            QString str = QString( "SimData: X: %1 Y: %2 Theta: %3" )
                .arg( data.objectPos.x )
                .arg( data.objectPos.y )
                .arg( data.objectPos.theta );
            ui->telemTxt->append( str );
        } );

    connect(
           _robotClient,
           & WestBot::ClientStuff::updateRobotPos,
           this,
           [ this ](
               uint8_t id,
               uint8_t color,
               double x,
               double y,
               double theta )
           {
               if( _robots.isEmpty() || ! _robots.contains( id )  )
               {
                   // No robot yet on the map or not the good one. create one
                   WestBot::Robot::Ptr robot =
                       std::make_shared< WestBot::Robot >( color );
                   _robots.insert( id, robot );
                   _scene->addItem( robot.get() );
                   robot->setPos( x * 0.2, y * 0.2  );
                   robot->setRotation( DEG( theta ) );
               }
               else
               {
                   const auto& robot = _robots.value( id );
                   robot->setPos( x * 0.2, y * 0.2  );
                   robot->setRotation( DEG( theta ) );
               }

               _scene->update();
           } );

       connect(
           _robotClient,
           & WestBot::ClientStuff::updatePuckPos,
           this,
           [ this ](
               uint8_t id,
               uint8_t color,
               double x,
               double y,
               bool onTable )
           {
               if( _pucks.isEmpty() || ! _pucks.contains( id )  )
               {
                   // No puck yet on the map or not the good one. create one
                   WestBot::Puck::Ptr puck =
                       std::make_shared< WestBot::Puck >( color );
                   _pucks.insert( id, puck );
                   _scene->addItem( puck.get() );
                   puck->setPos( x * 0.2, y * 0.2  );
               }
               else
               {
                   const auto& puck = _pucks.value( id );
                   puck->setPos( x * 0.2, y * 0.2  );
               }

               _scene->update();
           } );

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

void MainWindow::on_startBtn_clicked()
{
    _robotClient->send( "start" );
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->telemTxt->clear();
}
