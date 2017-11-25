#include "playerobject.h"
#include "bullet.h"
#include "enemy.h"

#include <QTimer>
#include <QtMath>
#include <QGraphicsScene>
#include <QDebug>
#include <typeinfo>
#include <stdlib.h> //rand()

//SLots and Signals
Enemy::Enemy(char size, float before_x, float before_y)
{
    type = size;
    //Set truth bool to true.
    ifExist = true;

    //Define dimensions
    //width = 144;
    //height = 146;

    if (type == 'B')
    {
        width = 144;
        height = 146;
        qDebug() << "B made.";

        setPixmap(QPixmap(":/new/files/black_ball.png"));
    }
    else if (type == 'M')
    {
        width = 100;
        height = 72;//etc.

        qDebug() << "M made.";

        setPixmap(QPixmap(":/new/files/black_ball_M.png"));
    }
    else if (type == 'S')
    {
        qDebug() << "S made.";

        width = 60;
        height = 40;//etc.

        setPixmap(QPixmap(":/new/files/black_ball_S.png"));
    }

    //Random Position
    int random_x = qrand() % 800;
    int random_y = qrand() % 600;

    //Random Angle. Maybe not needed.
    angle = qrand() % 360;

    //Standard speed
    speed = 1.5;
    if (size == 'B')
        speed = 1.5;
    else if (size == 'M')
        speed = 2.5;
    else if (size == 'S')
        speed = 3.5;
    else
        speed = 1.5;

    //At a given angle.
    setTransformOriginPoint(width/2, height/2);
    setRotation(angle);

    //Key X/Y changes in the velocity.
    speed_y = -speed*cos(qDegreesToRadians(angle));
    speed_x = speed*sin(qDegreesToRadians(angle));

    //Last astroid position.
    before_X = before_x;
    before_Y = before_y;

    //Repositions lower sized enemies.
    if ((type == 'M') || (type == 'S'))
    {
        qDebug() << "before_x: " << before_x;
        qDebug() << "before_y: " << before_y;

        setPos(before_X , before_Y);
    }
    else
        setPos(random_x, random_y);
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

void Enemy::setType(char input)
{
    type = input;
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

    int count, n;
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If bullet collides with enemy destroy both.
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(myRect))
        {
            ifExist = false;

            scene()->removeItem(this);
            //delete this;
        }
        else if (typeid(*(colliding_items[count])) == typeid(Bullet))
        {
            qDebug() << "Hit by Bullet";
            ifExist = false;

            scene()->removeItem(colliding_items[count]);
            scene()->removeItem(this);

            delete colliding_items[count];
        }
    }

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
