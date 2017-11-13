#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Enemy();
public slots:
    void move();

private:
    float angle;

    int width;
    int height;

    float speed;
    float speed_x;
    float speed_y;

};


#endif // ENEMY_H
