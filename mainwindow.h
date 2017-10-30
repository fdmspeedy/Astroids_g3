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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Scene;
class QUndoStack;
class QUndoView;
class QPrinter;

#include <QMainWindow>

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();                       // constructor

public slots:
  void showMessage( QString );        // show message on status bar
  void showUndoStack();               // open up undo stack window
  void fileNew();                     // start new simulation
  bool fileSaveAs();                  // save simulation to file returning true if successful
  bool fileOpen();                    // load simulation file returning true if successful
  void filePrintPreview();            // display print preview dialog
  void filePrint();                   // display print dialog
  void print( QPrinter* );            // draw print page

protected:
  void closeEvent( QCloseEvent* );    // check if user really wants to exit

private:
  Scene*       m_scene;               // scene representing the simulated landscape
  QUndoStack*  m_undoStack;           // undo stack for undo & redo of commands
  QUndoView*   m_undoView;            // undo stack window to view undo & redo commands
};

#endif  // MAINWINDOW_H
