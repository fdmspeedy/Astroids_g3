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
}

//width: 800, height: 600.
void Enemy::move()//Is being called periodcally.
{
    int pos_x = (qrand() % 800);
    int pos_y = (qrand() % 600);


    //move the enemy " Random ".
    setPos(x()+10, y()+10);
    if ((pos().y() + rect().height()) >= 600) //When bottom is touched, set to top.
    {
        setPos(pos_x, 0); //(x, y)
    }
    if ((pos().x() + rect().width()) >= 800) //Simple.
    {
        setPos(0, pos_y);
    }
}
