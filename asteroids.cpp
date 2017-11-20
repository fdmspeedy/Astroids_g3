/*************************************************************************************/

/******************* Represents an asteroid in the simulation ************************/

/*************************************************************************************/

#include <QGraphicsScene>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QObject>
#include <QPointF>
#include <typeinfo>
#include "asteroids.h"
#include "scene.h"

/****** Constructor ******/
Asteroid::Asteroid(){
    hit = false;
    size = rand()%3;
    xbounds=dw.width()*0.8;
    ybounds=dw.height()*0.8;
    setAngle(x_move, y_move);
    minMove = 5;
    QTimer *times = new QTimer();//checks for movement of asteroid based on time
    connect(times,SIGNAL(timeout()),this,SLOT(move()));
    times->start(50);
}

void  Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
  // paint asteroid, must be smaller than bounding rectangle
    QPointF origin;
    origin.setX(1);
    origin.setY(1);
    painter->setRenderHint( QPainter::Antialiasing );
    painter->setPen( QPen( Qt::white, 5 ) );
    if(size == 2)
        painter->drawEllipse(origin,60,60);
    else if(size == 1)
        painter->drawEllipse(origin,30,30);
    else if(size == 0)
        painter->drawEllipse(origin,15,15);

}

/***** Moves the asteroid in a randomly decided angle and velocity *****/
void Asteroid::move(){
    if(not hit){
        if(y_move<0 and y_move>minMove*-1)
            y_move = minMove*-1;
        else if(y_move>0 and y_move<minMove)
            y_move = minMove;
        if(x_move<0 and x_move>minMove*-1)
            x_move = minMove *-1;
        else if(x_move>0 and x_move<minMove)
            x_move = minMove;
        //Set the position of the asteroid
        setPos(x()-x_move,y()-y_move);

        //wraps asteroid around if it goes off screen
        if (x() >= xbounds)
            setPos(x() - xbounds,y());
        else if (x() <= 0)
            setPos(x()+xbounds,y());
        if (y() >= ybounds)
            setPos(x(),y() - ybounds);
        else if (y() <= 0)
            setPos(x(),y()+ybounds);
    }
    else
        return;
}

/****** Sets the angle that the asteroids move and how fast they move ******/
void Asteroid::setAngle(int& x, int& y){   
    x = rand()%20-10;
    y = rand()%20-10;
}
