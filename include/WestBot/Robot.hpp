// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef WESTBOT_ROBOT_HPP_
#define WESTBOT_ROBOT_HPP_

#include <QOpenGLWidget>

namespace WestBot {

class Robot : public QOpenGLWidget
{
public:
    Robot( QWidget* parent );

    void setPosition( int x, int y );

protected:
    void paintEvent( QPaintEvent* event ) override;
};

}

#endif // WESTBOT_ROBOT_HPP_
