#ifndef MYRECT
#define MYRECT
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

public slots:
    void spawn();
    void respond();

private:
    QTimer * player_timer;

    int enemy_amount = 1;
    float angle;

    int width;
    int height;

    float speed;
    float speed_x;
    float speed_y;
    //void DoCollision();

};

#endif // PLAYEROBJECT_H
