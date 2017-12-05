#ifndef MYRECT
#define MYRECT
#include "bullet.h"

#include <QGraphicsItem>
#include <animation_control.h>

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>

class myRect : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public: 
    //Passes Timer to Player for movement.	
    myRect(QTimer *);	
    
    //All Key pressing go to the Player.			
    void keyPressEvent(QKeyEvent * event);
	
    //Returns true if the Player pressed space to create a new bullet.
    bool returnSpacePressed();

    float giveAngle();  //Give Player Angle.
    float giveSpeedX(); //Give Player speed x.
    float giveSpeedY(); //Give Player speed y.
    int giveWidth();    //Give Player Width.
    int giveHeight();   //Give Player Height.
    int giveHealth();   //Give Player Health.

    void setTipShip();  //Update Player given front Ship position..
    float giveTipY();   //Give Player Tip Position Y.
    float giveTipX();   //Give Player Tip Position X.

public slots:
    void movement();    //Slot to Timer for Player movement.

private:
    QTimer * player_timer; //Records Timer in the player.
    bool spacePressed;     //Boolean for when Space is pressed.

    int player_health;     //Holds Player Health
    int bulletCooldown;    //Stalls Player Bullet command.

    float angle;           //Holds Current Angle.

    //Holds Player Width / Height.
    int width;
    int height;

    float speed;           //Player base speed.
    float speed_x;         //Player Stacked X speed.
    float speed_y;         //Player Stacked Y speed.

    //Holds position for bullet spawning.
    float shipFrontX;
    float shipFrontY;

};

#endif // PLAYEROBJECT_H
