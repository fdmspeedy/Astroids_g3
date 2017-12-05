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

//The Timer is passed for player movement.
myRect::myRect(QTimer * timer) : QGraphicsPixmapItem()
{
    player_health = 100.0; //Total starting health.

    spacePressed = false;  //Space has not been pressed yet.
    bulletCooldown = 0;    //Control of bullet pressing.

    player_timer = timer;  //Timer stored within Player.

    //Ship Width and Height.
    width = 50/2;
    height = 66/2;

    //Player Ship image.
    setPixmap(QPixmap(":/new/files/Standard_Ship_01.png")); //Ship image.

    //Sets the ship focusable so that commands go to the Player.
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    //Sets the point of rotation.
    //width: 79, height: 111 are the dimensions of the raw image for ship.
    setTransformOriginPoint(width, height);

    //Set Speed
    speed = 2.0;
    speed_x = 0.0;
    speed_y = 0.0;

    //Set Angle.
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

    //If space is pressed, and bullet cool down vairable are zero then continue.
    else if ((event->key() == Qt::Key_Space) && (!bulletCooldown))
    {
        spacePressed = true;

        //Sets bullet cool down to higher number as to be controlled by the Timer.
        bulletCooldown = 10;
    }
}

//Returns true if space was pressed.
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

//Give player Angle.
float myRect::giveAngle()
{
    return angle;
}

//Give player speed x.
float myRect::giveSpeedX()
{
    return speed_x;
}

//Give player speed y.
float myRect::giveSpeedY()
{
    return speed_y;
}

//Give player Width.
int myRect::giveWidth()
{
    return width;
}

//Give player Height.
int myRect::giveHeight()
{
    return height;
}

//Give PLayer Health.
int myRect::giveHealth()
{
    return player_health;
}

//Updates the Player varibles that Bullet position is based off of.
void myRect::setTipShip()
{
    shipFrontY = -(height)*cos(qDegreesToRadians(angle));
    shipFrontX = (width)*sin(qDegreesToRadians(angle));
}

//Give player Tip Y.
float myRect::giveTipY()
{
    return (y() + shipFrontY);
}

//Give player Tip X.
float myRect::giveTipX()
{
    return (x()+(width)+shipFrontX);
}

//Movement() helps the player move and is connected to the Timer.
void myRect::movement()
{
    int count, n;
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If player collides with enemy, lower player health..
    colliding_items = collidingItems();
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(Enemy))
        {
            player_health -= 25;
            qDebug() << "PLAYER HEALTH: " << player_health;

            return;
        }
    }

    //Counts down till player can shoot again.
    if (bulletCooldown != 0)
        bulletCooldown--;

    //Player velocity is being moved.setPos()
    //from: Top. To: Bottom.
    if (y() < 0)
        setPos(x() + speed_x, 580-speed_y);

    //from: Bottom. To: Top.
    else if (y() > 600)
        setPos(x() + speed_x, 3-speed_y);

    //From: Left side. To: Right Side.
    else if(x() < 0)
        setPos(790 + speed_x, y()-speed_y);

    //From: Right side. To: Left side.
    else if (x() > 800)
        setPos(3 + speed_x, y()-speed_y);

    //Normal Movement of Ship.
    else
        setPos(x()+ speed_x, y()-speed_y);
}

