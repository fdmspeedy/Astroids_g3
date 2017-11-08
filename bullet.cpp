#include "bullet.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include <typeinfo>

//SLots and Signals
Bullet::Bullet(): QObject(), QGraphicsPixmapItem()
{
    //Drew the Rect
    setPixmap(QPixmap(":/new/files/bullet_Purple.png"));

    //Connect
    QTimer * timer = new QTimer();
    //Connects the timeout signal to the move slot
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50); //50 milli-seconds
}

void Bullet::move()//Is being called periodcally.
{
    int count, n;
    //If bullet collides with enemy destroy both.
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(Enemy))
        {
            //Remove both*
            scene()->removeItem(colliding_items[count]);
            scene()->removeItem(this);

            //Freeing up memory used by deleted objects
            delete colliding_items[count];
            delete this;
            return;
        }
    }

    //move the bullet " up ".
    setPos(x(), y() - 9);
    if ((pos().y()) < 0) //Simple.
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Bullet Deleted ...";
    }
}
