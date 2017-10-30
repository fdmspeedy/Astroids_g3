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

#ifndef COMMANDSTATIONMOVE_H
#define COMMANDSTATIONMOVE_H

#include "station.h"

#include <QUndoCommand>

/*************************************************************************************/
/***************** Undostack command for moving a station on a scene *****************/
/*************************************************************************************/

class CommandStationMove : public QUndoCommand
{
public:
  CommandStationMove( Station* station, qreal fromX, qreal fromY, qreal toX, qreal toY )
  {
    m_station = station;
    m_from    = QPointF( fromX, fromY );
    m_to      = QPointF( toX, toY );
    setText( QString("Station move %1,%2 -> %3,%4").arg(fromX).arg(fromY).arg(toX).arg(toY) );
  }

  virtual void undo()    { m_station->setPos( m_from ); }

  virtual void redo()    { m_station->setPos( m_to ); }

private:
  Station*   m_station;       // station being moved
  QPointF    m_from;          // original coords
  QPointF    m_to;            // new coords
};

#endif  // COMMANDSTATIONMOVE_H
