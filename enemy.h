#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

#include <QMediaPlayer>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(char, float, float);
    char giveType();
    bool giveState();
    bool falseState();
    float givePosX();
    float givePosY();

    void setType(char);
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

    float before_X;
    float before_Y;


    QMediaPlayer * damageSound; //sound for new levels
};


#endif // ENEMY_H
