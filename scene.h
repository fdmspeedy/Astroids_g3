#ifndef SCENE_H
#define SCENE_H

//class QGraphicsSceneMouseEvent;
class QGraphicsSceneContextMenuEvent;
class QUndoStack;
class QXmlStreamWriter;
class QXmlStreamReader;
//class Station;

#include <QGraphicsScene>


/*************************************************************************************/
/******************** Scene representing the simulated landscape *********************/
/*************************************************************************************/

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
  Scene( QUndoStack* );                       // constructor
  //void  writeStream( QXmlStreamWriter* );     // write scene data to xml stream
  //void  readStream( QXmlStreamReader* );      // read scene data from xml stream

public slots:
  void new_game();
signals:
  void  message( QString );                                  // info text message signal

protected:
  //void  mousePressEvent( QGraphicsSceneMouseEvent* );        // receive mouse press events
  //void  contextMenuEvent( QGraphicsSceneContextMenuEvent* ); // receive context menu events

private:
  QUndoStack * m_undoStack;

};

#endif  // SCENE_H
