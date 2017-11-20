#include "enemy.h"
#include <QTimer>
#include <QtMath>
#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include <stdlib.h> //rand()

//SLots and Signals
Enemy::Enemy()
{ 
    //Set truth bool to true.
    ifExist = true;

    //Define dimensions
    width = 150;
    height = 120;

    //Random Position
    int random_x = qrand() % 800;
    int random_y = qrand() % 600;

    //Random Angle. Maybe not needed.
    angle = qrand() % 360;

    //Insert Image of astroid.
    setPixmap(QPixmap(":/new/files/astroid_image.png"));

    //Set Random position
    setPos(random_x, random_y);

    //Standard speed
    speed = 1.5;

    //At a given angle.
    setTransformOriginPoint(width/2, height/2);
    setRotation(angle);

    //Key X/Y changes in the velocity.
    speed_y = -speed*cos(qDegreesToRadians(angle));
    speed_x = speed*sin(qDegreesToRadians(angle));
}

char Enemy::giveType()
{
    return type;
}

bool Enemy::giveState()
{
    return ifExist;
}

bool Enemy::falseState()
{
    ifExist = false;
}

float Enemy::givePosX()
{
    return x();
}

float Enemy::givePosY()
{
    return y();
}

void Enemy::updateState()
{
    speed_y = -speed*cos(qDegreesToRadians(angle));
    speed_x = speed*sin(qDegreesToRadians(angle));
}

//width: 800, height: 600.
void Enemy::move()//Is being called periodcally.
{
    int pos_x;
    int pos_y = qrand() % 600;

    //qDebug() << "Enemy_X: " << x() << " Enemy_Y: " << y();
    //qDebug() << "Addess??: " << this;


    int count, n;
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If bullet collides with enemy destroy both.
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(Enemy))
        {
            qDebug() << "colliding with Enemy v Enemy";

            angle += 160;
            (angle < 0) ? angle += 360 : angle = angle;
            (angle > 360) ? angle -= 360 : angle = angle;

            count = n;
        }
    }

    updateState();

    //Width scene: 800, height scene: 600
    //move the enemy " Random ".
    setPos(x()+speed_x, y()+speed_y);

    //Enter: bottom. Exit: top side
    if ((y() + height) >= 700) //When bottom is touched, set to top.
    {
        pos_x = qrand() % 800; //Move to the x_axis position from touched y-axis.
        setPos(pos_x, 0); //(x, y)

        angle += qrand() % 45;
        if (angle > 360)
            angle -= 360;
        else if (angle < 0)
            angle += 360;


        setRotation(angle);

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
