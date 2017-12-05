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

    //Was an Enemy destroyed
    bool enemyDown();

    //Given angle,

private:

    QList<QGraphicsItem *> colliding_items;

    int b_width;  //Width of Bullet.
    int b_height; //Height of Bullet.

    float standard_speed; //Holds basic speed of a Bullet.
    
    //Holds Stacked speed of bullet			
    float speed_x;	  
    float speed_y;

    //Records enemy information.
    float enemy_X;
    float enemy_Y;

    bool ifExist;    //Records if it has been crashed.
    bool boogieDown; //Records if it has hit an Asteroid.

    QList<Enemy*> AstList; //Records encounters with Asteroids.



public slots:
    //Important function called by timer for bullet movement.
    void move();      
    void enemy_list(QList<Enemy*> &);
};


#endif // BULLET_H

