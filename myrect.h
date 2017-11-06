#ifndef MYRECT
#define MYRECT

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QObject> //TO make sure something inherits from o bject

class myRect : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    myRect(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);

    QRectF boundingRect() const;


protected:
    void advance(int phase);

public slots:
    void spawn();

private:
    int angle =0;

    qreal angle2;
    qreal speed = 5;
    //void DoCollision();

};

#endif // MYRECT

