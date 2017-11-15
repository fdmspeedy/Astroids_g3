#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
//#include <QtMath>
#include <QObject>

//Accompanying bullet class for ship.
class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();
    void updateBullet(float, float, float);

    //returns true if it hasn't collided with anything.
    bool giveExistance();

    //Changes ifExist variable to set up deletion.
    void falseExistance();

    //Given angle,

private:

    int b_width;
    int b_height;
    float standard_speed;
    float speed_x;
    float speed_y;

    bool ifExist;


public slots:
    void move();
};


#endif // BULLET_H

