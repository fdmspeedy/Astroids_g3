#include "playerobject.h"
#include "bullet.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTransform>

#include <QDebug>
#include <iostream>
#include <cmath>
#include <QtMath>
#include <QList>

using namespace std;

//Global list  for bullets
QList<Bullet *> bulletList;

//Create asteroid list
QList<Enemy *> enemyList;

//Constructor.
myRect::myRect() : QGraphicsPixmapItem()
{
    setPixmap(QPixmap(":/new/files/ship_01.png")); //Ship image.

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    //Sets the point of rotation.
    //width: 79, height: 111 are the dimensions of the raw image for ship.
    setTransformOriginPoint(width, height);

    //Set Speed
    speed = 2.0; //5 pixels at a time.
}


//When something is pressed, events come here.
//Ship is intended to rotate with left and right keys.
//Player then uses the up button to move in the direction that the ship is pointing at.
void myRect::keyPressEvent(QKeyEvent *event)
{
    //When left is pressed, this changes the angle of the coordinate system
    //and directino of ship.
    float move_x;
    float move_y;

    if (event->key() == Qt::Key_Left)
    {
        angle = angle-5.0;
        if (angle < 0)
            angle = angle + 360.0;
        else if (angle > 360)
            angle = angle - 360;

        if (pos().x() > 0)
        {
            setRotation(angle);
        }
    }
    else if (event->key() == Qt::Key_Right)
    {
        angle = angle+5.0;
        if (angle < 0)
            angle = angle + 360.0;
        else if (angle > 360)
            angle = angle - 360;
        if (pos().x() + 100 < 800)
        {
            setRotation(angle);//Rotates the item.
        }
    }

    //This moves the ship in the direction it is pointing at.
    else if (event->key() == Qt::Key_Up)
    {
        if (pos().y() > 0)
        {
            qDebug() << "(x, y): " << x() << " / " << y();
            //setPos((x, y)) sets the position of the ship.
            //#cos(angle).

            move_y = -speed*cos(qDegreesToRadians(angle));

            move_x = speed*sin(qDegreesToRadians(angle));

            qDebug() << "move_x: " << move_x
                     << " move_y: " << move_y;

            setPos(x() + move_x, y()+ move_y);

            speed_x = speed_x + move_x;
            speed_y = speed_y + (-move_y);
        }
    }
    else if (event->key() == Qt::Key_Down)
    {
    }
    else if (event->key() == Qt::Key_Space)
    {
        //Create Bullet.
        Bullet * bullet = new Bullet();

        //Add bullet to bulletList
        bulletList.append(bullet);

        //Set position of the bullet.
        bullet->setPos(x() + 40, y() - 54);

        //qDebug() << "Bullet created";
        scene()->addItem(bullet);
    }
}

//Determine coordinate points based off of Angle, speed, and previous position.
void myRect::find_pos(float & pos_x, float & pos_y)
{

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
    //Add enemy.
    if (enemy_amount == 1)
    {
        Enemy * enemy = new Enemy();
        scene()->addItem(enemy);

        //Add enemy to enemyList
        enemyList.append(enemy);

        enemy_amount++;
    }

    //Player velocity is being moved.setPos()
    setPos(x()+ speed_x, y()-speed_y);//speed_y

}
