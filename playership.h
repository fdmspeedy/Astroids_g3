#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <QGraphicsItem>
#include <QObject>

class playerShip : public QGraphicsRectItem
{
public:
    playerShip();
    void keyPressEvent (QKeyEvent *event); //When a key is pressed, use this function.

private:
    int width;
    int height;
};

/*#include <QGraphicsItem>
#include <QObject>
#include <animation_control.h>


//Focused player class.
class playerObject : public QGraphicsRectItem
{
//    Q_OBJECT
public:
    playerObject();//Constructor
    void keyPressEvent (QKeyEvent *event); //When a key is pressed, use this function.
private:
    int width;
    int height;
};

//Accompanying bullet class for ship.
class Bullet : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bullet();//Constructor
public slots:
    void move();//Movement fucntion for bullet.
};*/
#endif // PLAYERSHIP_H
