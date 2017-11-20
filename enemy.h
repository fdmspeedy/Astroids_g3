#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();
    char giveType();
    bool giveState();
    bool falseState();
    float givePosX();
    float givePosY();
    void updateState();

public slots:
    void move();

private:
    bool ifExist;

    char type; //Ranges from B, M, S

    float angle;

    int width;
    int height;

    float speed;
    float speed_x;
    float speed_y;

};


#endif // ENEMY_H
