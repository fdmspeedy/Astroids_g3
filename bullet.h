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

private:
    int b_width;
    int b_height;
    float standard_speed;
    float move_x;
    float move_y;


public slots:
    void move();
};


#endif // BULLET_H

