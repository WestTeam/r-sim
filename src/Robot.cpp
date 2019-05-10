// Copyright (c) 2019 All Rights Reserved WestBot

#include "include/WestBot/Robot.hpp"

#include <QPainter>

using namespace WestBot;

Robot::Robot(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setFixedSize( 60, 60 );
    setAutoFillBackground( false );
}

void Robot::paintEvent(QPaintEvent *event)
{
    QRectF tInitialPos(
        100.0,
        0.0,
        60.0,
        60.0 );
    QPainter painter( this );
    painter.drawImage( tInitialPos, QImage( ":/resources/red.png" ) );
}

void Robot::setPosition( int x, int y )
{
    this->move( x, y );
}
