/*************************************************************************************/

/******************* Represents a ship in the simulation *****************************/
/*************************************************************************************/
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QtMath>

#include "ship.h"
#include "scene.h"
#include "bullet.h"
#include "asteroids.h"

/************************************ constuctor *************************************/

Ship::Ship( qreal x, qreal y ) : QGraphicsItem()
{
    //Set Focus on the ship
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    // Set Ship pixmap and position
    setPos( x, y );

    // Set initial rotation angle
    rotation = 0;

    // Set Ships initial speed
    xaccel = 0;
    yaccel = 0;

    // Set boundaries of ship
    xbounds=dw.width()*0.8;
    ybounds=dw.height()*0.8;

    // Move Ship every 50 milliseconds
    QTimer *times = new QTimer();
    connect(times,SIGNAL(timeout()),this,SLOT(move()));
    times->start(50);
}



/****** Moves the ship ******/
void Ship::move(){
    if(not dead){
        //Sets position based on the acceleration of the ship
        if((xaccel > 0 or yaccel > 0) or (xaccel < 0 or yaccel < 0)){
            setPos(x()+xaccel,y()-yaccel);

            //wraps asteroid around if it goes off screen
            if (x() >= xbounds)
                setPos(x() - xbounds,y());
            else if (x() <= 0)
                setPos(x() + xbounds,y());
            if (y() >= ybounds)
                setPos(x(),y() - ybounds);
            else if (y() <= 0)
                setPos(x(), y() + ybounds);
        }
    }
}
/****** Creates a ship by drawing a rectangle and tracing a path ******/
void  Ship::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    //May create a bounds issue later when dealing with collisions (Untested)
    QRectF rect = QRectF(-10, -15, 25, 30);
    QPainterPath path;
    //Draw a triangle within QRectangle
    path.moveTo(rect.left() + (rect.width() / 2), rect.top());
    path.lineTo(rect.bottomLeft());
    path.lineTo(rect.bottomRight());
    path.lineTo(rect.left() + (rect.width() / 2), rect.top());
    //Paints the triangle
    painter->fillPath(path, QBrush(QColor ("white")));
}



