// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef WESTBOT_PUCK_HPP_
#define WESTBOT_PUCK_HPP_

#include <QGraphicsWidget>

namespace WestBot {

class Puck : public QGraphicsWidget
{
public:
    Puck( uint8_t type, QWidget* parent = nullptr );

    void setPosition( int x, int y );

protected:
    void paint(
        QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget ) override;

    QPainterPath shape() const override;

private:
    uint8_t _type;
};

}

#endif // WESTBOT_PUCK_HPP_
