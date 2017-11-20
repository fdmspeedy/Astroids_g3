/*************************************************************************************/

/******************* Represents the scene of the simulation **************************/

/*************************************************************************************/
#include <QTimer>
#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGlobal>
#include <QGraphicsPixmapItem>
#include <QStatusBar>

#include "asteroids.h"
#include "scene.h"
#include "ship.h"
#include "mainwindow.h"

/****** Constructor ******/
Scene::Scene() : QGraphicsScene()
{
  // create invisible item to provide default top-left anchor to scene
  addLine( 0, 0, 0, 1, QPen(Qt::transparent, 1) );
  addShip();
  s->setFocus();
  level = 1;
  over = false;
  nextLevel = false;
  for(int i = 0;i<5;i++)
    addAsteroid();
  QTimer * timer = new QTimer();
  connect(timer,SIGNAL(timeout()),this,SLOT(update()));//refreshes screen on a timer
  timer->start(50);

  QTimer * time = new QTimer();
  connect(time,SIGNAL(timeout()),this,SLOT(collidesWith()));//refreshes screen on a timer
  time->start(50);

}

/***** Adds ship to the scene *****/
void Scene::addShip(){
    // Create new ship in center of screen
    s= new Ship((dw.width()*0.8)/2 , (dw.height()*0.8)/2);

    // Add ship to the scene
    addItem(s);

    // Make it possible for user focus to be on ship
    s->setFlag(QGraphicsItem::ItemIsFocusable);

    //Sets focus on s, so it can be moved by player
    s->setFocus();
}

/***** Creates an asteroid and adds it to the scene *****/
void Scene::addAsteroid(){
    int coord_x, coord_y;
    //Create new Asteroid named "ast"
    Asteroid * ast = new Asteroid;
    // Set coordinates of asteroid to random position
    int zero = rand()%2;

    if(nextLevel){
        level++;
        ast->minMove*=2;
    }
    if(zero == 1){
        coord_x = rand()%dw.width()*0.8;
        coord_y = 1     ;

    }
    else{
        coord_x = 1;
        coord_y = rand()%dw.height()*0.8;
    }

    ast->setPos(coord_x, coord_y);

    //Add Asteroid to scene and list
    addItem(ast);
    roids.append(ast);

}

/********* Controls Ship by checking if certain keys have been pressed **********/
void Scene::keyPressEvent(QKeyEvent *event)
{
    if(not s->dead){
        //rotates left by subracting from rotation angle
        if(event->key() == Qt::Key_Left){
            if(s->rotation == 0) s->rotation = 360;
            s->setRotation(s->rotation -= 30);
        }

        //rotates right by adding to rotation angle
        else if(event->key() == Qt::Key_Right){
            if(s->rotation == 360) s->rotation = 0;
            s->setRotation(s->rotation += 30);
        }

        //moves ship relative to angle of rotation
        else if(event->key() == Qt::Key_Up){
            s->xaccel += 2*sin(s->rotation*(3.141592654/180));
            s->yaccel += 2*cos(s->rotation*(3.141592654/180));

            //limits ship speed
            if (s->xaccel > 15) s->xaccel = 15;
            if (s->yaccel > 15) s->yaccel = 15;
            if (s->xaccel < -15) s->xaccel = -15;
            if (s->yaccel < -15) s->yaccel = -15;
        }
//        else if(event->key() == Qt::Key_Down){
//            int dist = (qAbs(s->x() - roids[0]->x()) + qAbs(s->y() - roids[0]->y()));
//            qDebug() << "Estimated Distance: " << dist<< endl<<roids.length();
//        }
        //shoots bullet from ship
        else if(event->key() == Qt::Key_Space){

            //If there is less than 15 bullets on screen add one.
            if(bullets.length()<3){

                //Create new bullet
                Bullet * bull = new Bullet();

                //Set Position of the Bullet to match orientation of the ship
                bull->setPos(s->x() + (cos(s->rotation*(3.141592654/180))) , s->y() + (sin(s->rotation*(3.141592654/180))));
                bull->angle = s->rotation;
                bull->setRotation(s->rotation);

                //Add bullet to scene and list of bullets
                addItem(bull);
                bullets.append(bull);
            }

            //Check if bullets are on the screen, then check if they are out of bounds, if they are delete them.
            if(not bullets.isEmpty()){
                for(int i = 0;i<=bullets.length()-1; i++){
                    if(bullets[i]->collided == true){
                       // delete bullets[i];
                        bullets.removeAt(i);
                    }
                }
            }
        }
    }
}

/****** Checks for collision between ship, bullets, and asteroids ******/
void Scene::collidesWith(){
    //Dist is the estimated distance between two objects on the screen.
    //i and j are indixes for the for loops
    //hitDist is the error allowed for the distance between two objects
    int dist, i, j, hitDist;
    //Check if asteroids are on screen
    if(not roids.isEmpty()){
        for(i = 0; i<=roids.length()-1;i++){
            switch(roids[i]->size){
                case 2:
                    hitDist = 42;
                    break;
                case 1:
                    hitDist = 25;
                    break;
                case 0:
                    hitDist = 15 ;
                    break;
            }
            //Estimate distance between ship and asteroids
            dist = (qAbs(s->x() - roids[i]->x()) + qAbs(s->y() - roids[i]->y()))/2;
            //If estimated distance is less than 42 delete ship and asteroid
            if(dist <= hitDist and s->dead == false){
                //Kill the ship and remove it from the scene
                //s->dead=true;
                //removeItem(s);
                gameOver();
                //remove asteroid from scene and list and set hit variable to true
                //roids[i]->hit = true;
                //removeItem(roids[i]);
                //roids.removeAt(i);
            }
            //Check if list of bullets isn't empty
            if(not bullets.isEmpty() and roids.length()>=i){
                for(j = 0; j<=bullets.length()-1; j++){
                    //if(roids.length()>=i and roids[i]->hit == false){
                        //Estimate distance between bullet and asteroids
                        dist=(qAbs(bullets[j]->x()-roids[i]->x()) + qAbs(bullets[j]->y()-roids[i]->y()))/2;
                        //If distance is less than 42 delete bullet and asteroid
                        if(dist<=hitDist){

                            //Set bullets collided varible to true, remove it from scene and list
                            bullets[j]->collided = true;
                            removeItem(bullets[j]);
                            bullets.removeAt(j);

                            //Set roids hit variable to true and remove it from the scene
                            roids[i]->hit = true;
                            removeItem(roids[i]);

                            //Check if roid[i] is the smallest asteroid, if not it splits it.
                            if(roids[i]->size != 0){
                                splitAsteroid(roids[i]);
                                roids.removeAt(i);
                            }
                            else
                                roids.removeAt(i);
                        }
                    }
                }
            }
        }
    //}
    // If no asteroids on screen, add 5 more
    else if(not s->dead){
        nextLevel = true;
        for(i = 0; i<5; i++)
            addAsteroid();
    }
}
/****** Checks size of asteroid then splits or destroys accordingly ******/
void Scene::splitAsteroid(Asteroid* roid){
    //Create two new asteroids called split
    for(int i=0; i<2; i++){
        Asteroid* split = new Asteroid;
        //Set their position and rotation based off of parent asteroid
        split->setPos(roid->pos());
        /*if(i==0){
            split->x_move = roid ->x_move/2;
            split->y_move = roid ->y_move;
        }
        else{
            split->x_move = roid ->x_move;
            split->y_move = roid ->y_move/2;
        }*/
        split->setAngle(roid->x_move, roid->y_move);
        split->size = roid->size-1;

        //Add new child asteroid to list and scene
        roids.append(split);
        addItem(split);
    }
}
void Scene::gameOver(){
    over = true;
    s->dead=true;
    removeItem(s);
    while(not roids.isEmpty()){
        removeItem(roids.first());
        roids.first()->hit = true;
        roids.removeFirst();
    }
    while(not bullets.isEmpty()){
        removeItem(bullets.first());
        bullets.first()->collided = true;
        bullets.removeFirst();
    }
    itsAllOver="Game Over! You reached level: ";
    itsAllOver+=level;
}
