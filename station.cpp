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

#include "station.h"

#include <QPainter>

/*************************************************************************************/
/******************* Represents a radio station in the simulation ********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

Station::Station( qreal x, qreal y ) : QGraphicsItem()
{
  // set Station pixmap and position
  setPos( x, y );
  setFlags( QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIgnoresTransformations );
}

/************************************** paint ****************************************/

void  Station::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  // paint station symbol, must be smaller than bounding rectangle
  painter->setRenderHint( QPainter::Antialiasing );
  painter->setPen( QPen( Qt::black, 2 ) );
  painter->drawRect( -4,  -3,  8,   7 );
  painter->drawLine(  0,  -4,  0, -11 );
  painter->drawLine( -5, -11,  0,  -6 );
  painter->drawLine( +5, -11,  0,  -6 );
}
