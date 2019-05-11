// Copyright (c) 2019 All Rights Reserved WestBot

#include "include/WestBot/Robot.hpp"

#include <QPainter>

using namespace WestBot;

Robot::Robot( QWidget* parent )
    : QOpenGLWidget( parent )
{
    setFixedSize( 60, 60 );
    setAutoFillBackground( false );
}

void Robot::paintEvent( QPaintEvent* event )
{
    QPainter painter( this );
    painter.drawImage( this->rect(), QImage( ":/resources/red.png" ) );
}

void Robot::setPosition( int x, int y )
{
    this->move( x, y );
}
