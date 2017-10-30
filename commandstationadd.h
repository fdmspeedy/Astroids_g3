/***************************************************************************
 *   Copyright (C) 2009 by Richard Crook                                   *
 *   richard@dazzle.plus.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef COMMANDSTATIONADD_H
#define COMMANDSTATIONADD_H

#include <QUndoCommand>
#include <QGraphicsScene>

/*************************************************************************************/
/***************** Undostack command for adding a station to a scene *****************/
/*************************************************************************************/

class CommandStationAdd : public QUndoCommand
{
public:
  CommandStationAdd( QGraphicsScene* scene, qreal x, qreal y )
    {
      m_station = new Station( x, y );
      m_scene   = scene;
      setText( QString("Station add %1,%2").arg(x).arg(y) );
    }

  ~CommandStationAdd()
    {
      // if station not on scene then delete station
      if ( !m_scene->items().contains( m_station ) )
        delete m_station;
    }

  virtual void undo()    { m_scene->removeItem( m_station ); }

  virtual void redo()    { m_scene->addItem( m_station ); }

private:
  Station*         m_station;    // station being added
  QGraphicsScene*  m_scene;      // scene where station being added
};

#endif  // COMMANDSTATIONADD_H
