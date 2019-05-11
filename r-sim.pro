# Copyright (c) 2019 All Rights Reserved WestBot

QT += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = r-sim
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

INCLUDEPATH += include

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/Puck.cpp \
        src/RobotTcpClient.cpp \
        src/Robot.cpp

HEADERS += \
        include/WestBot/mainwindow.h \
        include/WestBot/RobotTcpClient.hpp \
        include/WestBot/Puck.hpp \
        include/WestBot/Robot.hpp

FORMS += mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
