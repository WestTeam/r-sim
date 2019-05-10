// Copyright (c) 2019 All Rights Reserved WestBot

#include <QApplication>

#include "include/WestBot/mainwindow.h"

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
