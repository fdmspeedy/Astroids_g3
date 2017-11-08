#include "scene.h"
#include "playerobject.h"

//#include <QGraphicsSceneMouseEvent>
//#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>
#include <QMenu>
#include <QTransform>
#include <QAction>
#include <QTimer>
#include <QDebug>

#include <QUndoStack>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Scene::Scene( QUndoStack* undoStack ) : QGraphicsScene()
{
  // initialise variables
  m_undoStack     = undoStack;

  // create invisible item to provide default top-left anchor to scene
  addLine( 0, 0, 0, 1, QPen(Qt::transparent, 1) );

  // connect selection Changed signal to selectStations slot
  connect( this, SIGNAL(selectionChanged()), this, SLOT(new_game()) );
}


//Define creation of player when new is hit.
void Scene::new_game()
{
    /*myRect *player = new myRect(); //Creating player
    addItem(player);
    //Set player in the middle.
    player->setPos(800 / 2, 600/ 2); //Set player in the middle.
    //Spawn Enemies

    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(1000/33); //Make an enemy every 2000 milli-seconds
    //new_game = false;*/
}

/************************************ writeStream ************************************/

/*void  Scene::writeStream( QXmlStreamWriter* stream )
{
  // write station data to xml stream
  foreach( QGraphicsItem*  item, items() )
  {
    Station*  station = dynamic_cast<Station*>( item );
    if ( station )
    {
      stream->writeEmptyElement( "station" );
      stream->writeAttribute( "x", QString("%1").arg(station->x()) );
      stream->writeAttribute( "y", QString("%1").arg(station->y()) );
    }
  }
}

/************************************ readStream *************************************/

/*void  Scene::readStream( QXmlStreamReader* stream )
{
  // read station data from xml stream
  while ( !stream->atEnd() )
  {
    stream->readNext();
    if ( stream->isStartElement() && stream->name() == "station" )
    {
      qreal x = 0.0, y = 0.0;
      foreach( QXmlStreamAttribute attribute, stream->attributes() )
      {
        if ( attribute.name() == "x" ) x = attribute.value().toString().toDouble();
        if ( attribute.name() == "y" ) y = attribute.value().toString().toDouble();
      }
      addItem( new Station( x, y ) );
    }
  }
}

/********************************** mousePressEvent **********************************/

/*void  Scene::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
  QTransform transform;
  transform.reset();

  // set local variables and check if existing station clicked
  qreal           x = event->scenePos().x();
  qreal           y = event->scenePos().y();
  Station*  station = dynamic_cast<Station*>(itemAt(x,y, transform));

  // if station not clicked and right mouse button pressed, create new Station
  if ( station == 0 && event->button() == Qt::LeftButton )
  {
    addItem( new Station( x, y ) );
    emit message( QString("Station add at %1,%2").arg(x).arg(y) );
  }
  // call base mousePressEvent to handle other mouse press events
  QGraphicsScene::mousePressEvent( event );
}


void  Scene::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
  QTransform transform;
  transform.reset();

  // we only want to display a menu if user clicked a station
  qreal     x       = event->scenePos().x();
  qreal     y       = event->scenePos().y();
  Station*  station = dynamic_cast<Station*>( itemAt( x, y, transform ) );
  if ( station == 0 ) return;

  // display context menu and action accordingly
  QMenu     menu;
  QAction*  deleteAction = menu.addAction("Delete Station");
  if ( menu.exec( event->screenPos() ) == deleteAction )
  {
    removeItem( station );
    delete station;
    emit message( QString("Station deleted at %1,%2").arg(x).arg(y) );
  }
}*/
