#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

//Accompanying bullet class for ship.
class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();
public slots:
    void move();
};


#endif // BULLET_H

