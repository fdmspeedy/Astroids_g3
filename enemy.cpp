#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <stdlib.h> //rand()

//SLots and Signals
Enemy::Enemy()
{
    int random_number = rand() % 700;
    //Set Random position
    setPos(random_number, 0);

    //Drew the Rect
    setRect(0,0, 100, 100);

    //Connect
    QTimer * timer = new QTimer();
    //Connects the timeout signal to the move slot
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50); //50 milli-seconds
}

void Enemy::move()//Is being called periodcally.
{
    //move the enemy " Random ".
    setPos(x(), y() + 10);
    if ((pos().y() + rect().height()) >= 800) //Simple.
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Enemy Deleted ...";
    }
}
