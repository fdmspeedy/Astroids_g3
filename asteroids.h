#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include <QDesktopWidget>
#include <QList>
#include <QGraphicsScene>

/*************************************************************************************/
/******************* Represents an asteroid in the simulation ********************/
/*************************************************************************************/
class Asteroid : public QObject, public QGraphicsItem//, public Scene
{
    Q_OBJECT
    public:
        Asteroid(); //default constructor
        void  paint( QPainter*, const QStyleOptionGraphicsItem*, QWidget* );
        QDesktopWidget dw; //Size of users screen
        double xbounds; //Xbounds of window
        double ybounds; //Ybounds of window
        void setAngle(int& x, int& y); //Decides which direction astroid flys
        bool hit;
        int size;
        int x_move; //How the asteroid moves in x direction
        int y_move; //How the asteroid moves in y direction
        int minMove; //Minimum speed of asteroids
        QRectF boundingRect() const{ //bounding rectangle allowing no screen movement
            return QRectF(0,0,0,0);
        }
    public slots:
        void move();
};
#endif // ASTEROIDS_H


