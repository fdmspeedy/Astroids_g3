#include <QApplication>
#include <QGraphicsScene>
#include "myrect.h"
#include <QGraphicsView>
#include <QTimer>

/*
Three major classes
-QGraphicsScene
-QGraphicsItem  (QGraphicsRectITem)
-QGrahpicsView (Widget)

Tutorial round 2
-events (KeyPressEvent() and QKeyEvent)
-event propogation system
-QDebug

Tutorial round 3
-QTimer
-Siginals and Slots (connect function)
-QObject and Q_Object macro

Tutorial round 4
-QGraphicsScene'e Scene Rect
-QGraphicsView's Scene Rect
-QGraphicView Coordinates vs QGraphicScene Coordinates vs QGraphicsItem Coordinates

Tutorial round 5
-collidingItems() (NEW)
-QTimer and coordinate systems (REVIEW)

Tutorial round 6 NA
-parents
-QGraphicsTextItem, setPlainText(), setFont(), setDefaultTextColor().

Tutorial round 7
-QGraphicsPixmapItem, QPixmap, QImage

*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Creates a Scene
    QGraphicsScene * scene = new QGraphicsScene();

    //Create an item into the scene.
    myRect * player = new myRect();
    //Change properties of Rectangle.
    //player->setRect(0,0, 100, 100); //(X, Y, width, height)

    //Add the item to the scene
    scene->addItem(player);

    //Make the rect ""focusable"". Not focused yet ...
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //Everything is conceptual and invisible until you display it onto a view.
    //add a View
    QGraphicsView * view = new QGraphicsView(scene);
    //Could also use: view->setScene(scene);

    //Disable the scroll bar for the scene to slove bullets extending the scene.
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    view->setFixedSize(800, 600);//Set the view to a fixed size.

    scene->setSceneRect(0,0, 800, 600);

    player->setPos(view->width() / 2, view->height()/ 2); //Set player in the middle.

    //Spawn Enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));

    timer->start(2000); //Make an enemy every 2000 milli-seconds


    return a.exec();
}
