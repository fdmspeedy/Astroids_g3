#ifndef BULLET_H
#define BULLET_H

#include "enemy.h"

#include <QGraphicsPixmapItem>
#include <QList>
//#include <QtMath>
#include <QObject>

//Accompanying bullet class for ship.
class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();

    //Updates velocity to the bullet based on the player.
    void updateBullet(float, float, float);

    //returns true if it hasn't collided with anything.
    bool giveExistance();

    //Changes ifExist variable to set up deletion.
    void falseExistance();

    //Give enemy information
    float giveEnemyX();
    float giveEnemyY();

    //Introduce list and return with changed version.
    //void enemy_list(QList<Enemy*> &);//List, X, Y

    //Was an Enemy destroyed
    bool enemyDown();

    //Given angle,

private:

    QList<QGraphicsItem *> colliding_items;

    int b_width;
    int b_height;
    float standard_speed;
    float speed_x;
    float speed_y;

    float enemy_X;
    float enemy_Y;

    bool ifExist;
    bool boogieDown;

    QList<Enemy*> AstList;



public slots:
    void move();
    void enemy_list(QList<Enemy*> &);
};


#endif // BULLET_H

