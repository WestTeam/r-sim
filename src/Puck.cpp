// Copyright (c) 2019 All Rights Reserved WestBot

#include "include/WestBot/Puck.hpp"

#include <QPainter>

using namespace WestBot;

namespace
{
    const double COEFF_REDUC = 0.2;
    const double PUCK_R = 38.1;
}

Puck::Puck( QWidget* parent, uint8_t type )
    : QOpenGLWidget( parent )
    , _type( type )
{
    setFixedSize( PUCK_R * 2 * COEFF_REDUC, PUCK_R * 2 * COEFF_REDUC );
    setAutoFillBackground( false );
}

void Puck::paintEvent( QPaintEvent* event )
{
    QPainter puck( this );

    if( _type == 0 )
    {
        puck.drawImage( this->rect(), QImage( ":/resources/red.png" ) );
    }
    else if( _type == 1 )
    {
        puck.drawImage( this->rect(), QImage( ":/resources/green.png" ) );
    }
    else
    {
        puck.drawImage( this->rect(), QImage( ":/resources/blue.png" ) );
    }

    /*// Cote A
    QRectF tRed1(
        ( 500.0 - PUCK_R ) * COEFF_REDUC,
        ( 450.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tRed2(
        ( 500.0 - PUCK_R ) * COEFF_REDUC,
        ( 750.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tRed3(
        ( 1050.0 - PUCK_R ) * COEFF_REDUC,
        ( 1050.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tRed4(
        ( 1000.0 - PUCK_R ) * COEFF_REDUC,
        ( 1150.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tGreen1(
        ( 500.0 - PUCK_R ) * COEFF_REDUC,
        ( 1050.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tGreen2(
        ( 900.0 - PUCK_R ) * COEFF_REDUC,
        ( 1050.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tBlue1(
        ( 1000.0 - PUCK_R ) * COEFF_REDUC,
        ( 950.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QPainter redium1( this );
    redium1.drawImage( tRed1, QImage( ":/resources/red.png" ) );

    QPainter redium2( this );
    redium2.drawImage( tRed2, QImage( ":/resources/red.png" ) );

    QPainter redium3( this );
    redium3.drawImage( tRed3, QImage( ":/resources/red.png" ) );

    QPainter redium4( this );
    redium4.drawImage( tRed4, QImage( ":/resources/red.png" ) );

    QPainter greenium1( this );
    greenium1.drawImage( tGreen1, QImage( ":/resources/green.png" ) );

    QPainter greenium2( this );
    greenium2.drawImage( tGreen2, QImage( ":/resources/green.png" ) );

    QPainter blueium1( this );
    blueium1.drawImage( tBlue1, QImage( ":/resources/blue.png" ) );

    // Cote B
    QRectF tRed1B(
        ( 2500.0 - PUCK_R ) * COEFF_REDUC,
        ( 450.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tRed2B(
        ( 2500.0 - PUCK_R ) * COEFF_REDUC,
        ( 750.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tRed3B(
        ( 2050.0 - PUCK_R ) * COEFF_REDUC,
        ( 1150.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tRed4B(
        ( 2000.0 - PUCK_R ) * COEFF_REDUC,
        ( 950.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tGreen1B(
        ( 2500.0 - PUCK_R ) * COEFF_REDUC,
        ( 1050.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tGreen2B(
        ( 2100.0 - PUCK_R ) * COEFF_REDUC,
        ( 1050.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QRectF tBlue1B(
        ( 1900.0 - PUCK_R ) * COEFF_REDUC,
        ( 1050.0 - PUCK_R ) * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC,
        PUCK_R * 2 * COEFF_REDUC );

    QPainter redium1B( this );
    redium1B.drawImage( tRed1B, QImage( ":/resources/red.png" ) );

    QPainter redium2B( this );
    redium2B.drawImage( tRed2B, QImage( ":/resources/red.png" ) );

    QPainter redium3B( this );
    redium3B.drawImage( tRed3B, QImage( ":/resources/red.png" ) );

    QPainter redium4B( this );
    redium4B.drawImage( tRed4B, QImage( ":/resources/red.png" ) );

    QPainter greenium1B( this );
    greenium1B.drawImage( tGreen1B, QImage( ":/resources/green.png" ) );

    QPainter greenium2B( this );
    greenium2B.drawImage( tGreen2B, QImage( ":/resources/green.png" ) );

    QPainter blueium1B( this );
    blueium1B.drawImage( tBlue1B, QImage( ":/resources/blue.png" ) );
    */
}

void Puck::setPosition( int x, int y )
{
    this->move( x, y );
}
