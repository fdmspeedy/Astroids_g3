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
    ifExist = true;  //Sets if it exists to true.

    b_width = 10/2;  //Given half Width.
    b_height = 54/2; //Given half Height

    standard_speed = 5.0;
    //move_x = standard_speed + speed_x;
    //move_y = standard_speed + speed_y;

    //Use image to represent bullet in the scene.
    setPixmap(QPixmap(":/new/files/bullet_Purple.png"));

    //Setting point where the bullet will be rotated around.
    setTransformOriginPoint(b_width, b_height);
}

void Bullet::updateBullet(float angle, float delta_x, float delta_y)
{

    //It works. Don't Touch it. :)
    //Uses Trig to determine which additions and subtractions
    //to add to current position for it move.
    speed_x = (standard_speed)*sin(qDegreesToRadians(angle));
    speed_y = -(standard_speed)*cos(qDegreesToRadians(angle));

    //Rotates the bullet to the angle of the player.
    setRotation(angle);

    //Stack the speed of the ship to the speed of the bullet.
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

//Returns encountered Asteroid Pos.
float Bullet::giveEnemyX()
{
    return enemy_X;
}

//Returns encountered Asteroid Pos.
float Bullet::giveEnemyY()
{
    return enemy_Y;
}

//Returns true if contact with an Asteroid is there.
bool Bullet::enemyDown()
{
    boogieDown = false;
    return true;
}

//Recording current Asteroid List.
void Bullet::enemy_list(QList<Enemy *> & aList)
{
    AstList = aList;
}

//Move() is called constantly by the Timer for this Bullet to move across the screen.
//Is being called periodcally.
void Bullet::move()
{
    int count, n;

    //If bullet collides with enemy destroy both.
    colliding_items = collidingItems();
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(Enemy))
        {

            //Records enemy position.
            enemy_X = colliding_items[count]->x();
            enemy_Y = colliding_items[count]->y();

            //Remove both from the scene.
            //scene()->removeItem(colliding_items[count]);
            //scene()->removeItem(this);

            //Update State Booleans.
            ifExist = false;
            boogieDown = true;

            return;
        }
    }

    //Updates the Position of the Bullet.
    setPos(x() + speed_x, y() + speed_y);

    //When the bullet goes beyond the bounds, delete it.
    if ((y() < 0) || (y() > 600) || (x() < 0) || (x() > 800))
    {
        scene()->removeItem(this);
        ifExist = false;
        delete this;
        qDebug() << "Bullet Deleted ...";
    }
}
