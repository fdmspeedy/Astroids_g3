#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Enemy();
    char giveType();
public slots:
    void move();

private:
    char type; //Ranges from B, M, S

    float angle;

    int width;
    int height;

    float speed;
    float speed_x;
    float speed_y;

};


#endif // ENEMY_H
