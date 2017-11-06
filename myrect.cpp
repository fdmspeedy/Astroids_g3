#include "myrect.h"
#include "bullet.h"
#include "enemy.h"
#include<QGraphicsScene>
#include<QKeyEvent>
#include <QTransform>


#include<QDebug>
#include<iostream>
#include<cmath>

using namespace std;

//Constructor.
myRect::myRect(QGraphicsItem *parent) : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/new/Images/ship_01.png")); //Ship image.

    //Sets the point of rotation.
    //79, 111 are the dimensions of the raw image for ship.
    setTransformOriginPoint(79/2, 111/2);

    //Set Speed
    speed = 5; //5 pixels at a time.
}


//When something is pressed, events come here.
//Ship is intended to rotate with left and right keys.
//Player then uses the up button to move in the direction that the ship is pointing at.
void myRect::keyPressEvent(QKeyEvent *event)
{
    //When left is pressed, this changes the angle of the coordinate system
    //and directino of ship.
    if (event->key() == Qt::Key_Left)
    {
        angle = angle-5;
        if (pos().x() > 0)
        {
            setRotation(angle);
        }
    }
    else if (event->key() == Qt::Key_Right)
    {
        angle = angle+5;
        if (pos().x() + 100 < 800)
        {
            setRotation(angle);//Rotates the item.
        }
        qDebug() << "Angle: " << angle;

    }

    //This moves the ship in the direction it is pointing at.
    else if (event->key() == Qt::Key_Up)
    {
        if (pos().y() > 0)
        {
            //setPos(x(), y()-5); //Move to the up by 10.
            qDebug() << "(x, y): " << x() << " / " << y();
            qDebug() << "maptoParent " << mapToParent(0, -5);

            //setPos((x, y)) sets the position of the ship.
            //maptoParent should use the point of the local item and transfer
            //it to the scene coordinates.
            setPos( mapToParent(0, -5));
        }
    }
    else if (event->key() == Qt::Key_Down)
    {
        if (pos().y() + 100 < 600)
            setPos(x(), y()+5); //Move to the down by 10.
    }
    else if (event->key() == Qt::Key_Space)
    {
        //Create Bullet.
        Bullet * bullet = new Bullet();

        //Set position of the bullet.
        bullet->setPos(x() + 40, y() - 54);

        //qDebug() << "Bullet created";
        scene()->addItem(bullet);
    }
}

QRectF myRect::boundingRect() const
{
    return QRectF(0, 0, 79, 111);
}

void myRect::advance(int phase)
{
    if (!phase)
        return;

    QPointF location = this->pos();
    setPos( mapToParent(0, -(speed)) );
}

void myRect::spawn()
{
    //Add Enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}
