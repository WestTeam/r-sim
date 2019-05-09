// Copyright (c) 2019 All Rights Reserved WestBot

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
public:
    GLWidget( QWidget *parent );

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
