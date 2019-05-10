// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef WESTBOT_TABLE_HPP_
#define WESTBOT_TABLE_HPP_

#include <QOpenGLWidget>

namespace WestBot {

class Table : public QOpenGLWidget
{
public:
    Table( QWidget* parent );

protected:
    void paintEvent( QPaintEvent* event ) override;
};

}

#endif // WESTBOT_TABLE_HPP_
