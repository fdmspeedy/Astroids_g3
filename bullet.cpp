#include "bullet.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QVariant>
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

void Bullet::updateBullet(float angle, float delta_x, float delta_y)
{

    //It works. Don't Touch it. :)
    speed_x = (standard_speed)*sin(qDegreesToRadians(angle));
    speed_y = -(standard_speed)*cos(qDegreesToRadians(angle));

    setRotation(angle);

    speed_x += delta_x;
    speed_y -= delta_y;
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

//Return collided item
float Bullet::giveEnemyX()
{
    return enemy_X;
}

float Bullet::giveEnemyY()
{
    return enemy_Y;
}

bool Bullet::enemyDown()
{
    boogieDown = false;
    return true;
}

void Bullet::enemy_list(QList<Enemy *> & aList)
{
    qDebug() << "AFAFASFASFASFD";
    AstList = aList;
}

//angle, speed, position.
void Bullet::move()//Is being called periodcally.
{
    int count, n;
    //If bullet collides with enemy destroy both.
    colliding_items = collidingItems();
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(Enemy))
        {

            //Remove both from the scene.
            scene()->removeItem(colliding_items[count]);
            scene()->removeItem(this);

            //qDebug() << "holding?: " << holding;
            qDebug() << "DATA?: " << & colliding_items[count];
            qDebug() << "DATA W/ * ?: ";

            qDebug() << "DATA X?: " << colliding_items[count]->x();
            qDebug() << "DATA y?: " << colliding_items[count]->y();
            //qDebug() << "Adress??: " << colliding_items[count][0];

            enemy_X = colliding_items[count]->x();
            enemy_Y = colliding_items[count]->y();

            qDebug() << "Move(): enemy_X: " << enemy_X;
            qDebug() << "Move(): enemy_Y: " << enemy_Y;

            //Freeing up memory used by deleted objects
            delete colliding_items[count];
            delete this;

            //Sets variables to false in order to set up for deletion.
            ifExist = false;
            boogieDown = true;

            return;
        }
    }

    //move the bullet " up ".
    //qDebug() << "x(): " << x() << " y(): " << y();
    //qDebug() << "The constant changes within bullet:";
    //qDebug() << "move_x: " << move_x << " move_y: " << move_y;

    setPos(x() + speed_x, y() + speed_y);

    //When the bullet goes beyond the bounds.
    if ((y() < 0) || (y() > 600) || (x() < 0) || (x() > 800))
    {
        scene()->removeItem(this);
        ifExist = false;
        delete this;
        qDebug() << "Bullet Deleted ...";
    }
}
