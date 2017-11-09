#ifndef MYRECT
#define MYRECT
#include <QGraphicsItem>
#include <animation_control.h>

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>

class myRect : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    myRect();
    void keyPressEvent(QKeyEvent * event);
    void find_pos(float &, float&);

    QRectF boundingRect() const;

protected:
    void advance(int phase);

public slots:
    void spawn();

private:
    int enemy_amount = 1;
    float angle =0;

    int width = 79/2;
    int height = 111/2;

    float speed = 0;
    float speed_x;
    float speed_y;
    //void DoCollision();

};

#endif // PLAYEROBJECT_H
