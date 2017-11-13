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
    void updateLevel(int);

public slots:
    void spawn();
    void respond();

private:
    QTimer * player_timer;

    int level = 1;
    int enemy_amount = 2;
    int limit;

    float angle;

    int width;
    int height;

    float speed;
    float speed_x;
    float speed_y;
    //void DoCollision();

};

#endif // PLAYEROBJECT_H
