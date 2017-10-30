#include "playership.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QKeyEvent>
#include<QDebug>

//Goal: Details of Ship Controls, and intialization.

playerShip::playerShip() : QGraphicsRectItem()
{
    height = 100;
    width = 100;

    //Sets the player object on the scene.
    setRect(0, 0, width, height);

    //Current View: 1200, 700
    //Places player object in the middle.
    setPos( 600-(width/2), 300-(height/2) );

    //Makes the ship focused. Meaning control events fall into it.
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

//When any one key event occurs, its instance is passed here.
void playerShip::keyPressEvent(QKeyEvent *event)
{
    //Move to the right by 10.
    if (event->key() == Qt::Key_Right)
    {
        if (pos().x() + 100 < 800)
            setPos(x() + 5, y());
    }
    //Move to the left by 10.
    else if (event->key() == Qt::Key_Left)
    {
        if (pos().x() > 0)
            setPos(x()-5, y());
    }
    else if (event->key() == Qt::Key_Down)
    {
        setPos(x(), y() + 5);
    }
    else if (event->key() == Qt::Key_Up)
    {
        setPos(x(), y() - 5);
    }
    /*Launches a bullet if space pressed.
    else if (event->key() == Qt::Key_Space)
    {
        //Create Bullet.
        Bullet * bullet = new Bullet();

        //Set position of the bullet.
        bullet->setPos(x() + (width/2), y() - (height/3) );

        //qDebug() << "Bullet created";
        scene()->addItem(bullet);
    }*/
}

