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
    , _robotClient( this )
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

    /*
    WestBot::Robot* r1 = new WestBot::Robot( 0 );
    r1->setRect( -30, -30, 60, 60 ); // change the rect from 0x0 (default) to 100x100 pixels
    r1->setPos( 280 * 0.2, 600 * 0.2 );
    r1->setFlag( QGraphicsItem::ItemIsFocusable );
    _scene->addItem( r1 );

    WestBot::Robot* r2 = new WestBot::Robot( 1 );
    r2->setRect( -30, -30, 60, 60 ); // change the rect from 0x0 (default) to 100x100 pixels
    r2->setPos( 2720 * 0.2, 600 * 0.2 );
    r2->setFlag( QGraphicsItem::ItemIsFocusable );
    _scene->addItem( r2 );

    // A Side
    WestBot::Puck* red1 = new WestBot::Puck( 0 );
    red1->setPos( 500 * 0.2, 450.0 * 0.2 );
    _scene->addItem( red1 );

    WestBot::Puck* red2 = new WestBot::Puck( 0 );
    red2->setPos( 500 * 0.2, 750.0 * 0.2 );
    _scene->addItem( red2 );

    WestBot::Puck* red3 = new WestBot::Puck( 0 );
    red3->setPos( 1050.0 * 0.2, 1050.0 * 0.2 );
    _scene->addItem( red3 );

    WestBot::Puck* red4 = new WestBot::Puck( 0 );
    red4->setPos( 1000.0 * 0.2, 1150.0 * 0.2 );
    _scene->addItem( red4 );

    WestBot::Puck* green1 = new WestBot::Puck( 1 );
    green1->setPos( 500 * 0.2, 1050.0 * 0.2 );
    _scene->addItem( green1 );

    WestBot::Puck* green2 = new WestBot::Puck( 1 );
    green2->setPos( 900.0 * 0.2, 1050.0 * 0.2 );
    _scene->addItem( green2 );

    WestBot::Puck* blue1 = new WestBot::Puck( 2 );
    blue1->setPos( 1000.0 * 0.2, 950.0 * 0.2 );
    _scene->addItem( blue1 );

    // B SIDE
    WestBot::Puck* red1B = new WestBot::Puck( 0 );
    red1B->setPos( 2500 * 0.2, 450.0 * 0.2 );
    _scene->addItem( red1B );

    WestBot::Puck* red2B = new WestBot::Puck( 0 );
    red2B->setPos( 2500 * 0.2, 750.0 * 0.2 );
    _scene->addItem( red2B );

    WestBot::Puck* red3B = new WestBot::Puck( 0 );
    red3B->setPos( 2050.0 * 0.2, 1150.0 * 0.2 );
    _scene->addItem( red3B );

    WestBot::Puck* red4B = new WestBot::Puck( 0 );
    red4B->setPos( 2000.0 * 0.2, 950.0 * 0.2 );
    _scene->addItem( red4B );

    WestBot::Puck* green1B = new WestBot::Puck( 1 );
    green1B->setPos( 2500 * 0.2, 1050.0 * 0.2 );
    _scene->addItem( green1B );

    WestBot::Puck* green2B = new WestBot::Puck( 1 );
    green2B->setPos( 2100.0 * 0.2, 1050.0 * 0.2 );
    _scene->addItem( green2B );

    WestBot::Puck* blue1B = new WestBot::Puck( 2 );
    blue1B->setRect( -30, -30, 60, 60 ); // change the rect from 0x0 (default) to 100x100 pixels
    blue1B->setPos( 1900.0 * 0.2, 1050.0 * 0.2 );
    blue1B->setFlag( QGraphicsItem::ItemIsFocusable );
    _scene->addItem( blue1B );
*/
    ui->gameView->setRenderHint( QPainter::Antialiasing );
    ui->gameView->setCacheMode(QGraphicsView::CacheBackground);
    ui->gameView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

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

    connect(
        & _robotClient,
        & WestBot::RobotTcpClient::updateRobotPos,
        this,
        [ this ](
            uint8_t id,
            uint8_t color,
            int x,
            int y,
            int theta )
        {
            qDebug() << "Robot get signal" << id << " " << color << " " << x << " " << y << " " << theta;

            if( _robots.isEmpty() || ! _robots.contains( id )  )
            {
                // No robot yet on the map or not the good one. create one
                WestBot::Robot::Ptr robot =
                    std::make_shared< WestBot::Robot >( color );
                _robots.insert( id, robot );
                robot->setRect( -30, -30, 60, 60 ); // change the rect from 0x0 (default) to 100x100 pixels
                _scene->addItem( robot.get() );
            }
            else
            {
                const WestBot::Robot::Ptr& robot = _robots.value( id );
                robot->setPos( x * 0.2, y * 0.2 );
                robot->setRotation( theta );
            }
        } );

    connect(
        & _robotClient,
        & WestBot::RobotTcpClient::updatePuckPos,
        this,
        [ this ](
            uint8_t id,
            uint8_t color,
            int x,
            int y,
            bool onTable )
        {
            qDebug() << "Puck get signal" << id << " " << color << " " << x << " " << y << " " << onTable;

            if( _pucks.isEmpty() || ! _pucks.contains( id )  )
            {
                // No puck yet on the map or not the good one. create one

                WestBot::Puck::Ptr puck =
                    std::make_shared< WestBot::Puck >( color );
                _pucks.insert( id, puck );
                puck->setRect( -(15.24/2), -(15.24/2), 15.24, 15.24 );
                _scene->addItem( puck.get() );
            }
            else
            {
                const WestBot::Puck::Ptr& puck = _pucks.value( id );
                puck->setPos( x * 0.2, y * 0.2 );
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
    // TODO: XXX
}
