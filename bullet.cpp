/*************************************************************************************/

/********************** Represents a bullet in the simulation ************************/

/*************************************************************************************/
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QPainter>
#include <typeinfo>
#include "scene.h"
#include "bullet.h"
#include "asteroids.h"

/****** Constructor ******/
Bullet::Bullet()
{
    collided = false;
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));//does movement based on a timer
    timer->start(20);

}

/****** controls movement of bullet ******/
void Bullet::move()
{
    if(not collided){
        //Check if bullet is off screen and deletes it if it is
        if(x() >= dw.width()*0.8 or x() <= 0 or y() >= dw.height()*0.8 or y() <= 0){
            collided = true;
            scene()->removeItem(this);
            return;
        }
        //Move the bullet with respect to its angle
        setPos(x() + 20*sin(angle*(3.141592654/180)),y()- 20*cos(angle*(3.141592654/180)));
    }
    else
        return;
}
void Bullet::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget)// implement virtual paint function
{
    painter->setPen( QPen( Qt::white, 2 ) );
    painter->drawRect(0,0,2,5);//the bullet
}

