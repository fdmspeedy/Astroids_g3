#include "playerobject.h"
#include "bullet.h"
#include "enemy.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTransform>
#include <QDebug>
#include <typeinfo>
#include <iostream>
#include <cmath>
#include <QtMath>

using namespace std;

//Constructor.
//The Timer is passed in order to create bullet and astroid movement.
myRect::myRect(QTimer * timer) : QGraphicsPixmapItem()
{
    player_health = 100.0; //Total starting health.

    spacePressed = false;

    player_timer = timer;

    //Ship Width and Height.
    width = 50/2;
    height = 66/2;

    setPixmap(QPixmap(":/new/files/Standard_Ship_01.png")); //Ship image.

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    //Sets the point of rotation.
    //width: 79, height: 111 are the dimensions of the raw image for ship.
    setTransformOriginPoint(width, height);

    //Set Speed
    speed = 2.0;
    speed_x = 0.0;
    speed_y = 0.0;

    angle = 0.0;
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

    //When User presses the Left key.
    if (event->key() == Qt::Key_Left)
    {
        //Change the Angle to the Left by 5 Degress.
        angle = angle-5.0;

        //Adjust Angle if it goes beyond 0 to 360 Degrees.
        if (angle < 0.0)
            angle = angle + 360.0;

        else if (angle > 360.0)
            angle = angle - 360.0;

        //Rotate by the Angle.
        if (pos().x() > 0)
        {
            setRotation(angle);
        }
    }

    //When User presses the Right key.
    else if (event->key() == Qt::Key_Right)
    {
        //Change the Angle to the Left by 5 Degress.
        angle = angle+5.0;

        //Adjust Angle if it goes beyond 0 to 360 Degrees.
        if (angle < 0.0)
            angle = angle + 360.0;

        else if (angle > 360.0)
            angle = angle - 360;

        //Rotate by the Angle.
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
            //qDebug() << "(x, y): " << x() << " / " << y();

            //It works. Don't Touch it. :)
            move_y = -speed*cos(qDegreesToRadians(angle));
            move_x = speed*sin(qDegreesToRadians(angle));

            //qDebug() << "move_x: " << move_x << " move_y: " << move_y;

            setPos(x() + move_x, y()+ move_y);
            //This stacks the speed of the ship when going in one direction too much.
            speed_x = speed_x + move_x;
            speed_y = speed_y + (-move_y);
        }
    }

    //Possible brake button.
    else if (event->key() == Qt::Key_Down)
    {

    }
    else if (event->key() == Qt::Key_Space)
    {
        spacePressed = true;
        //Create Bullet.
        /*Bullet * bullet = new Bullet();

        //Set position of the bullet.
        bullet->setPos(x() + (50/2), y()-(66/2));
        bullet->updateBullet(angle, speed_x, speed_y);

        //qDebug() << "Bullet created";
        scene()->addItem(bullet);

        QObject::connect(player_timer, SIGNAL(timeout()), bullet, SLOT(move()));*/
    }
}

bool myRect::returnSpacePressed()
{
    bool relay;
    if (spacePressed)
        relay = true;
    else
        relay = false;
    spacePressed = false;
    return relay;
}

float myRect::giveAngle()
{
    return angle;
}

float myRect::giveSpeedX()
{
    return speed_x;
}

float myRect::giveSpeedY()
{
    return speed_y;
}

int myRect::giveWidth()
{
    return width;
}

int myRect::giveHeight()
{
    return height;
}

/*void myRect::updateLevel(int given_level)
{
    level = given_level;
}

void myRect::createEnemy(int limit)
{
    int count;
    for (count = 0; count < limit; count++)
    {
        //qDebug() << "Enemy being made...";
        //qDebug() << "Count: " << count;
        Enemy * enemy = new Enemy();
        scene()->addItem(enemy);
        QObject::connect(player_timer, SIGNAL(timeout()), enemy, SLOT(move()));
    }
    qDebug() << "Within Creating Enemy func.";
}*/

void myRect::movement()
{
    int count, n;

    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If bullet collides with enemy destroy both.
    colliding_items = collidingItems();
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(Enemy))
        {
            //Remove both from the scene.
            scene()->removeItem(colliding_items[count]);

            delete colliding_items[count];

            player_health -= 15;

            return;
        }
    }


    //Player velocity is being moved.setPos()
    setPos(x()+ speed_x, y()-speed_y);//speed_y
}

