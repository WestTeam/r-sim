// Copyright (c) 2019 All Rights Reserved WestBot

#include <qmath.h>

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPainter>

#include "include/WestBot/Robot.hpp"

using namespace WestBot;

Robot::Robot( uint8_t type, QWidget* parent )
    : _angle( 0 )
    , _speed( 0 )
    , _type( type )
    , _color( _type == 0 ? Qt::yellow : Qt::magenta )
{
}

void Robot::setPosition( int x, int y, int angle )
{
    //setPos( x, y, angle );
}

//
// Protected methods
//
void Robot::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* style,
    QWidget* widget )
{
    painter->setBrush(
        scene()->collidingItems(this).isEmpty() ? _color : Qt::red );
    painter->drawRect( -30, -30, 60, 60 );
    painter->setRenderHint( QPainter::Antialiasing );
    update();
}

QPainterPath Robot::shape() const
{
    QPainterPath path;
    path.addRect( -30, -30, 60, 60 );
    return path;
}

//
// Private methods
//
void Robot::keyPressEvent( QKeyEvent* event )
{
    // THIS IS FOR TEST PURPOSE ONLY
    if( event->key() == Qt::Key_Left )
    {
        setPos( x() - 10, y() );
    }
    else if( event->key() == Qt::Key_Right )
    {
        setPos( x() + 10, y() );
    }
    else if( event->key() == Qt::Key_Up )
    {
        setPos( x(), y() - 10 );
    }
    else if( event->key() == Qt::Key_Down )
    {
        setPos( x(), y() + 10 );
    }
    else if( event->key() == Qt::Key_Space )
    {
        _angle += 1.0;
        setRotation( _angle );
    }
}
