// Copyright (c) 2019 All Rights Reserved WestBot

#include <QPainter>

#include "include/WestBot/Table.hpp"

using namespace WestBot;

Table::Table( QWidget* parent )
    : QOpenGLWidget ( parent )
{
    setFixedSize( 600, 400 );
    setAutoFillBackground( true );
}

void Table::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );

    // Draw the map
    QPainter painter( this);
    painter.drawImage( this->rect(), QImage( ":/resources/table.png" ) );
}
