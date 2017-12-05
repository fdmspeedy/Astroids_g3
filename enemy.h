#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

#include <QMediaPlayer>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(char, float, float); //Sets up the Asteroid.
    char giveType();	       //Gives its Size.
    bool giveState();	       //Gives its State.
    bool falseState();         //Updates its State. 
    float givePosX();          //Give Position X.
    float givePosY();          //Give Position Y.

    void setType(char);        //Set what Size it is.
    void updateState();        //Call to change its traits.

public slots:
    void move();               //Movement function to the Timer.

private:
    bool ifExist;   //Existance State Boolean.

    char type;      //What Size the Asteroid is - Ranges from B, M, S

    float angle;    //Angle of movement.

    //Width and Height
    int width;   
    int height;

    float speed;    //Standard movement speed.
    float speed_x;  //Stacked speed.
    float speed_y;

    //Previous Asteroid position.
    float before_X;
    float before_Y;

    QMediaPlayer * damageSound; //sound for new levels
};


#endif // ENEMY_H
