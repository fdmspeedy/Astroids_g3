#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>


//Accompanying bullet class for ship.
class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();

    //list  for bullets
   // QList<Bullet *> bulletList;

private:

public slots:
    void move();
};


#endif // BULLET_H

