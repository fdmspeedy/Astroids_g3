#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T14:43:53
#
#-------------------------------------------------

QT       += core gui\
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    ship.cpp \
    bullet.cpp \
    asteroids.cpp

HEADERS  += mainwindow.h \
    scene.h \
    ship.h \
    bullet.h \
    asteroids.h

FORMS    += mainwindow.ui
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
