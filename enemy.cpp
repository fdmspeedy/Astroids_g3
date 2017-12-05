#include "playerobject.h"
#include "bullet.h"
#include "enemy.h"

#include <QTimer>
#include <QtMath>
#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include <stdlib.h> //rand()
#include <QMediaPlayer>

//SLots and Signals
Enemy::Enemy(char size, float before_x, float before_y)
{
    type = size;        //Saves what Type it is.
    ifExist = true;     //Sets truth bool to true.

    //Based on what type it is, it adjusts its characterisitics.
    if (type == 'B')
    {
        width = 144;
        height = 146;

        setPixmap(QPixmap(":/new/files/black_ball.png"));
    }
    else if (type == 'M')
    {
        width = 100;
        height = 72;

        setPixmap(QPixmap(":/new/files/black_ball_M.png"));
    }
    else if (type == 'S')
    {
        width = 60;
        height = 40;
        setPixmap(QPixmap(":/new/files/black_ball_S.png"));
    }

    //Random Position
    int random_x = qrand() % 800;
    int random_y = qrand() % 600;

    //Random Angle. Maybe not needed.
    angle = qrand() % 360;

    //Standard speed, and speed is also changed based on Size.
    speed = 1.5;
    if (size == 'B')
        speed = 1.5;
    else if (size == 'M')
        speed = 2.5;
    else if (size == 'S')
        speed = 3.5;
    else
        speed = 1.5;

    //At a given angle, change its angle.
    setTransformOriginPoint(width/2, height/2);
    setRotation(angle);

    //Key X/Y changes in the velocity.
    speed_y = -speed*cos(qDegreesToRadians(angle));
    speed_x = speed*sin(qDegreesToRadians(angle));

    //Last astroid position.
    before_X = before_x;
    before_Y = before_y;

    //Repositions lower sized enemies based on "before" Asteroids Position.
    if ((type == 'M') || (type == 'S'))
    {
        setPos(before_X , before_Y);
    }
    else
        setPos(random_x, random_y);         //Random poitison if a 'B' type.
    //Play sound when bullet is created
    //damageSound = new QMediaPlayer();
    //damageSound->setMedia(QUrl("qrc:/new/files/OUCH.wav"));

}

//Gives Size.
char Enemy::giveType()
{
    return type;
}

//Gives State..
bool Enemy::giveState()
{
    return ifExist;
}

//Updates State..
bool Enemy::falseState()
{
    ifExist = false;
}

//Gives Position X.
float Enemy::givePosX()
{
    return x();
}

//Gives Position Y.
float Enemy::givePosY()
{
    return y();
}

//Sets Size.
void Enemy::setType(char input)
{
    type = input;
}

//Updates State Speeds.
void Enemy::updateState()
{
    speed_y = -speed*cos(qDegreesToRadians(angle));
    speed_x = speed*sin(qDegreesToRadians(angle));
}

//Move() is called by the Timer and controls the movement of the Asteroids.
//Is being called periodcally.
void Enemy::move()
{
    //Hold random positions.
    int pos_x;
    int pos_y = qrand() % 600;
    int count, n;   //Loop variables.

    //List of Colliding Items.
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If bullet collides with enemy destroy both.
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(myRect))
        {
            ifExist = false;           //Set State to false.

            scene()->removeItem(this); //Remove from the scene.

        }
        else if (typeid(*(colliding_items[count])) == typeid(Bullet))
        {
            ifExist = false;           //Set State to false.

            //Removes Colliding Items from the scene.
            scene()->removeItem(colliding_items[count]);
            scene()->removeItem(this);

            //Delete bullet from scene as its information is not important.
            delete colliding_items[count];
        }
    }

    //move the enemy " Random ".
    setPos(x()+speed_x, y()+speed_y);

    //Enter: bottom. Exit: top side
    if ((y() + height) >= 700) //When bottom is touched, set to top.
    {
        pos_x = qrand() % 800; //Move to the x_axis position from touched y-axis.
        setPos(pos_x, 0); //(x, y)

        //Control Angle.
        angle += qrand() % 45;
        if (angle > 360)
            angle -= 360;
        else if (angle < 0)
            angle += 360;

        //Rotate by given Angle.
        setRotation(angle);

        //Speed and direction.
        speed_y = -speed*cos(qDegreesToRadians(angle));
        speed_x = speed*sin(qDegreesToRadians(angle));
    }

    //Enter: top. Exit: the left side
    else if ((y() + height) < -100)
    {
        pos_y = qrand() % 600;
        setPos(0, pos_y);

        angle += 45;
        if (angle > 360)
            angle -= 360;
        else if (angle < 0)
            angle += 360;

        setRotation(angle);

        speed_y = -speed*cos(qDegreesToRadians(angle));
        speed_x = speed*sin(qDegreesToRadians(angle));

    }

    //Enter: Left side. Exit: Right side
    else if ((x() + width) < -100)
    {
        pos_y = qrand() % 600;
        setPos(800, pos_y);

        angle += qrand() % 45;
        if (angle > 360)
            angle -= 360;
        else if (angle < 0)
            angle += 360;

        setRotation(angle);

        speed_y = -speed*cos(qDegreesToRadians(angle));
        speed_x = speed*sin(qDegreesToRadians(angle));

    }

    //Enter: Right Side. Exit: Bottom Side.
    else if ((x() + width) >= 900)
    {
        pos_x = qrand() % 800;
        setPos(pos_x, 600);

        angle -= 90;
        if (angle > 360)
            angle -= 360;
        else if (angle < 0)
            angle += 360;

        setRotation(angle);

        speed_y = -speed*cos(qDegreesToRadians(angle));
        speed_x = speed*sin(qDegreesToRadians(angle));
    }

}
