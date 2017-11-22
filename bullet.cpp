#include "bullet.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <cmath>
#include <QtMath>
#include <QList>
#include <typeinfo>

//SLots and Signals
Bullet::Bullet(): QObject(), QGraphicsPixmapItem()
{
    ifExist = true;

    b_width = 10/2;
    b_height = 54/2;

    standard_speed = 5.0;
    //move_x = standard_speed + speed_x;
    //move_y = standard_speed + speed_y;

    //Drew the Rect
    setPixmap(QPixmap(":/new/files/bullet_Purple.png"));

    setTransformOriginPoint(b_width, b_height);
}

void Bullet::updateBullet(float angle, float speed_x, float speed_y)
{
    //It works don't touch it.            

    move_x = (standard_speed + speed_x)*sin(qDegreesToRadians(angle));
    move_y = -(standard_speed + speed_y)*cos(qDegreesToRadians(angle));

    setRotation(angle);
}

//Returns current state
bool Bullet::giveExistance()
{
    return ifExist;
}

//Sets existance of current to false
//and sets up bullet for deletion.
void Bullet::falseExistance()
{
    ifExist = false;
}

//angle, speed, position.
void Bullet::move()//Is being called periodcally.
{
    int count, n;
    //If bullet collides with enemy destroy both.
    /*QList<QGraphicsItem *> colliding_items = collidingItems();
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(Enemy))
        {
            //Remove both*
            scene()->removeItem(colliding_items[count]);
            scene()->removeItem(this);

            //Freeing up memory used by deleted objects
            delete colliding_items[count];
            delete this;

            return;
        }
    }*/

    //move the bullet " up ".
    //qDebug() << "x(): " << x() << " y(): " << y();
    //qDebug() << "move_x: " << move_x << " move_y: " << move_y;

    setPos(x() + move_x, y() + move_y);

    //When the bullet goes beyond the bounds.
    if ((y() < 0) || (y() > 600) || (x() < 0) || (x() > 800))
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Bullet Deleted ...";
    }
}
