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
    myRect(QTimer *);
    void keyPressEvent(QKeyEvent * event);
    bool returnSpacePressed();
    float giveAngle();
    float giveSpeedX();
    float giveSpeedY();
    int giveWidth();
    int giveHeight();

public slots:
    void movement();

private:
    QTimer * player_timer;
    bool spacePressed;

    int player_health;

    float angle;

    int width;
    int height;

    float speed;
    float speed_x;
    float speed_y;

};

#endif // PLAYEROBJECT_H
