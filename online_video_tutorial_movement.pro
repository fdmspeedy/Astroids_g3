#-------------------------------------------------
#
# Project created by QtCreator 2017-10-25T13:11:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = online_video_tutorial_movement
TEMPLATE = app


SOURCES += main.cpp \
    myrect.cpp \
    bullet.cpp \
    enemy.cpp

HEADERS  += \
    myrect.h \
    bullet.h \
    enemy.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
