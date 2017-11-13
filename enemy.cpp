#include "enemy.h"
#include <QTimer>
#include <QtMath>
#include <QGraphicsScene>
#include <QDebug>
#include <stdlib.h> //rand()

//SLots and Signals
Enemy::Enemy()
{
    width = 100;
    height = 100;

    //Random Position
    int random_x = qrand() % 800;
    int random_y = qrand() % 600;

    //Random Angle. Maybe not needed.
    angle = qrand() % 360;

    //Drew the Rect
    setRect(0,0, width, height);

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

//width: 800, height: 600.
void Enemy::move()//Is being called periodcally.
{
    int pos_x;
    int pos_y = qrand() % 600;

    //move the enemy " Random ".
    setPos(x()+speed_x, y()+speed_y);

    if ((y() + height) >= 800) //When bottom is touched, set to top.
    {
        pos_x = qrand() % 600; //Move to the x_axis.
        setPos(pos_x, 0); //(x, y)

        angle += 45;
        if (angle > 360)
            angle -= 360;
        else if (angle < 0)
            angle += 360;

        setRotation(angle);

        speed_y = -speed*cos(qDegreesToRadians(angle));
        speed_x = speed*sin(qDegreesToRadians(angle));
    }

    else if ((y() + height) < 0)
    {
        pos_y = qrand() % 800;
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
    else if ((x() + width) < 0)
    {
        pos_x = qrand() % 600;
        setPos(pos_x, 0);

        angle += 45;
        if (angle > 360)
            angle -= 360;
        else if (angle < 0)
            angle += 360;

        setRotation(angle);

        speed_y = -speed*cos(qDegreesToRadians(angle));
        speed_x = speed*sin(qDegreesToRadians(angle));

    }
    else if ((x() + width) >= 600) //Simple.
    {
        pos_y = qrand() % 800;
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

}
