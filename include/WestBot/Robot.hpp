// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef WESTBOT_ROBOT_HPP_
#define WESTBOT_ROBOT_HPP_

#include <memory>

#include <QGraphicsItem>

namespace WestBot {

class Robot : public QGraphicsRectItem
{
public:
    using Ptr = std::shared_ptr< Robot >;

    Robot( uint8_t type, QWidget* parent = nullptr );

    void setPosition( int x, int y, int angle );

protected:
    void paint(
        QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget ) override;

    QPainterPath shape() const override;

private:
    void keyPressEvent( QKeyEvent* event );

private:
    qreal _angle;
    qreal _speed;
    uint8_t _type;
    QColor _color;
};

}

#endif // WESTBOT_ROBOT_HPP_
