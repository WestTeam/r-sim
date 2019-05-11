// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef WESTBOT_PUCK_HPP_
#define WESTBOT_PUCK_HPP_

#include <QOpenGLWidget>

namespace WestBot {

class Puck : public QOpenGLWidget
{
public:
    Puck( QWidget* parent, uint8_t type );

    void setPosition( int x, int y );

protected:
    void paintEvent( QPaintEvent* event ) override;

private:
    uint8_t _type;
};

}

#endif // WESTBOT_PUCK_HPP_
