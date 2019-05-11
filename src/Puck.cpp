// Copyright (c) 2019 All Rights Reserved WestBot

#include <QPainter>

#include "include/WestBot/Puck.hpp"

using namespace WestBot;

namespace
{
    const double COEFF_REDUC = 0.2;
    const double PUCK_R = 38.1;
}

Puck::Puck( uint8_t type, QWidget* parent )
    : _type( type )
{
}

//
// Private methods
//
void Puck::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if( _type == 0 )
    {
        painter->setBrush( Qt::red );
    }
    else if( _type == 1 )
    {
        painter->setBrush( Qt::green );
    }
    else
    {
        painter->setBrush( Qt::blue );
    }

    painter->drawEllipse( -( 15.24 / 2 ), -( 15.24 / 2), 15.24, 15.24 );
    painter->setRenderHint( QPainter::Antialiasing );
}

QPainterPath Puck::shape() const
{
    QPainterPath path;
    path.addRect( -(15.24/2), -(15.24/2), 15.24, 15.24 );
    return path;
}
