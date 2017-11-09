#-------------------------------------------------
#
# Project created by QtCreator 2017-10-22T22:36:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = playground2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    playerobject.cpp \
    animation_control.cpp \
    bullet.cpp \
    enemy.cpp

HEADERS  += mainwindow.h \
    scene.h \
    playerobject.h \
    animation_control.h \
    enemy.h \
    bullet.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
