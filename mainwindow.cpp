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

#include "mainwindow.h"
#include "scene.h"
#include <playership.h>

#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>
#include <QUndoStack>
#include <QUndoView>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDateTime>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QToolBar>

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

/************************************ constuctor *************************************/

MainWindow::MainWindow() : QMainWindow()
{
    setFixedSize(1200, 700);
  // add drop down menus
  QMenu*  fileMenu = menuBar()->addMenu( "&File" );
  //QMenu*  editMenu = menuBar()->addMenu( "&Edit" );
 // QMenu*  viewMenu = menuBar()->addMenu( "&View" );
  menuBar()->addMenu( "&Simulate" );
  menuBar()->addMenu( "&Help" );

  // create file menu options
  QAction* newAction     = fileMenu->addAction( "&New",              this, SLOT(fileNew()) );
//  QAction* saveAction    = fileMenu->addAction( "&Save As...",       this, SLOT(fileSaveAs()) );
 // QAction* openAction    = fileMenu->addAction( "&Open ...",         this, SLOT(fileOpen()) );
  fileMenu->addSeparator();
//  QAction* previewAction = fileMenu->addAction( "Print pre&view...", this, SLOT(filePrintPreview()) );
//  QAction* printAction   = fileMenu->addAction( "&Print...",         this, SLOT(filePrint()) );
  fileMenu->addSeparator();
                           fileMenu->addAction( "&Quit",             this, SLOT(close()) );
  newAction->setShortcut( QKeySequence::New );
 // saveAction->setShortcut( QKeySequence::Save );
 // openAction->setShortcut( QKeySequence::Open );
 // printAction->setShortcut( QKeySequence::Print );

  // create undo stack and associated menu actions
/*  m_undoStack = new QUndoStack( this );
  m_undoView  = 0;
  viewMenu->addAction( "Undo stack", this, SLOT(showUndoStack()) );
  QAction* undoAction = m_undoStack->createUndoAction( this );
  QAction* redoAction = m_undoStack->createRedoAction( this );
  undoAction->setShortcut( QKeySequence::Undo );
  redoAction->setShortcut( QKeySequence::Redo );
  editMenu->addAction( undoAction );
  editMenu->addAction( redoAction );
*/
  // create toolbar, set icon size, and add actions
  QToolBar*   toolBar = addToolBar( "Standard" );
  QStyle*     style   = this->style();
  QSize       size    = style->standardIcon(QStyle::SP_DesktopIcon).actualSize( QSize(99,99) );
  toolBar->setIconSize( size );
  newAction->setIcon( style->standardIcon(QStyle::SP_DesktopIcon) );
 /* openAction->setIcon( style->standardIcon(QStyle::SP_DialogOpenButton) );
  saveAction->setIcon( style->standardIcon(QStyle::SP_DialogSaveButton) );
  previewAction->setIcon( style->standardIcon(QStyle::SP_FileDialogContentsView) );
  printAction->setIcon( style->standardIcon(QStyle::SP_ComputerIcon) );
  undoAction->setIcon( style->standardIcon(QStyle::SP_ArrowBack) );
  redoAction->setIcon( style->standardIcon(QStyle::SP_ArrowForward) );
  toolBar->addAction( newAction );
  toolBar->addAction( openAction );
  toolBar->addAction( saveAction );
  toolBar->addSeparator();
  toolBar->addAction( previewAction );
  toolBar->addAction( printAction );
  toolBar->addSeparator();
  toolBar->addAction( undoAction );
  toolBar->addAction( redoAction );
*/
  //Make Player
  playerShip *player = new playerShip(); //Creating player

  // create scene and central widget view of scene
  m_scene               = new Scene( m_undoStack );
  QGraphicsView*   view = new QGraphicsView( m_scene );
  view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
  view->setFrameStyle( 0 );
  setCentralWidget( view );

  m_scene->addItem(player);//Add Player to Scene

  // connect message signal from scene to showMessage slot
  connect( m_scene, SIGNAL(message(QString)), this, SLOT(showMessage(QString)) );

  // add status bar message
  statusBar()->showMessage("QSimulate has started");
}

/************************************ showMessage ************************************/

void  MainWindow::showMessage( QString msg )
{
  // display message on main window status bar
  statusBar()->showMessage( msg );
}

/*********************************** showUndoStack ***********************************/
/*
void  MainWindow::showUndoStack()
{
  // open up undo stack window
  if ( m_undoView == 0 )
  {
    m_undoView = new QUndoView( m_undoStack );
    m_undoView->setWindowTitle( "QSimulate - Undo stack" );
    m_undoView->setAttribute( Qt::WA_QuitOnClose, false );
  }
  m_undoView->show();
}
*/
/************************************ fileSaveAs *************************************/

bool  MainWindow::fileSaveAs()
{
  // get user to select filename and location
  QString filename = QFileDialog::getSaveFileName();
  if ( filename.isEmpty() ) return false;

  // open the file and check we can write to it
  QFile file( filename );
  if ( !file.open( QIODevice::WriteOnly ) )
  {
    showMessage( QString("Failed to write to '%1'").arg(filename) );
    return false;
  }

  // open an xml stream writer and write simulation data
  QXmlStreamWriter  stream( &file );
  stream.setAutoFormatting( true );
  stream.writeStartDocument();
  stream.writeStartElement( "qsimulate" );
  stream.writeAttribute( "version", "2009-05" );
  stream.writeAttribute( "user", QString(getenv("USERNAME")) );
  stream.writeAttribute( "when", QDateTime::currentDateTime().toString(Qt::ISODate) );
  m_scene->writeStream( &stream );
  stream.writeEndDocument();

  // close the file and display useful message
  file.close();
  showMessage( QString("Saved to '%1'").arg(filename) );
  return true;
}

/************************************* fileOpen **************************************/

bool  MainWindow::fileOpen()
{
  // get user to select filename and location
  QString filename = QFileDialog::getOpenFileName();
  if ( filename.isEmpty() ) return false;

  // open the file and check we can read from it
  QFile file( filename );
  if ( !file.open( QIODevice::ReadOnly ) )
  {
    showMessage( QString("Failed to open '%1'").arg(filename) );
    return false;
  }

  // open an xml stream reader and load simulation data
  QXmlStreamReader  stream( &file );
  Scene*            newScene = new Scene( m_undoStack );
  while ( !stream.atEnd() )
  {
    stream.readNext();
    if ( stream.isStartElement() )
    {
      if ( stream.name() == "qsimulate" )
        newScene->readStream( &stream );
      else
        stream.raiseError( QString("Unrecognised element '%1'").arg(stream.name().toString()) );
    }
  }

  // check if error occured
  if ( stream.hasError() )
  {
    file.close();
    showMessage( QString("Failed to load '%1' (%2)").arg(filename).arg(stream.errorString()) );
    delete newScene;
    return false;
  }

  // close file, display new scene, delete old scene, and display useful message
  file.close();
  m_undoStack->clear();
  QGraphicsView*   view = dynamic_cast<QGraphicsView*>( centralWidget() );
  view->setScene( newScene );
  delete m_scene;
  m_scene = newScene;
  showMessage( QString("Loaded '%1'").arg(filename) );
  return true;
}

/********************************* filePrintPreview **********************************/

void  MainWindow::filePrintPreview()
{
  // display print preview dialog
  QPrinter             printer( QPrinter::ScreenResolution ); // QPrinter::HighResolution );
  QPrintPreviewDialog  preview( &printer, this );
  connect( &preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
  preview.exec();
}

/************************************ filePrint **************************************/

void  MainWindow::filePrint()
{
  // display print dialog and if accepted print
  QPrinter       printer( QPrinter::ScreenResolution );
  QPrintDialog   dialog( &printer, this );
  if ( dialog.exec() == QDialog::Accepted ) print( &printer );
}

/*************************************** print ***************************************/

void  MainWindow::print( QPrinter* printer )
{
  // create painter for drawing print page
  QPainter painter( printer );
  int      w = printer->pageRect().width();
  int      h = printer->pageRect().height();
  QRect    page( 0, 0, w, h );

  // create a font appropriate to page size
  QFont    font = painter.font();
  font.setPixelSize( (w+h) / 100 );
  painter.setFont( font );

  // draw labels in corners of page
  painter.drawText( page, Qt::AlignTop    | Qt::AlignLeft, "QSimulate" );
  painter.drawText( page, Qt::AlignBottom | Qt::AlignLeft, QString(getenv("USERNAME")) );
  painter.drawText( page, Qt::AlignBottom | Qt::AlignRight,
                    QDateTime::currentDateTime().toString( Qt::DefaultLocaleShortDate ) );

  // draw simulated landscape
  page.adjust( w/20, h/20, -w/20, -h/20 );
  m_scene->render( &painter, page );
}

/************************************** fileNew **************************************/

void  MainWindow::fileNew()
{
  // if no stations (only default top-left scene anchor) then nothing to do
  if ( m_scene->items().count() <= 1 ) return;

  // check if user wants to save before starting new simulation
  while (true)
    switch ( QMessageBox::warning( this, "QSimulate",
        "Do you want to save before starting new?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel ) )
    {
      case QMessageBox::Save:
        // if save not successful ask again
        if ( !fileSaveAs() ) break;

      case QMessageBox::Discard:
        // start new simulation
        {
          m_undoStack->clear();
          Scene*          newScene = new Scene( m_undoStack );
          QGraphicsView*  view     = dynamic_cast<QGraphicsView*>( centralWidget() );
          view->setScene( newScene );
          delete m_scene;
          m_scene = newScene;
        }
        return;

      default:    // "Cancel"
        return;
    }
}

/************************************ closeEvent *************************************/

void  MainWindow::closeEvent( QCloseEvent* event )
{
  // if no stations (only default top-left scene anchor) exists then accept close event
  if ( m_scene->items().count() <= 1 )
  {
    event->accept();
    return;
  }

  // check if user wants to save before quitting
  while (true)
    switch ( QMessageBox::warning( this, "QSimulate",
        "Do you want to save before you quit?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel ) )
    {
      case QMessageBox::Save:
        // if save not successful ask again
        if ( !fileSaveAs() ) break;

      case QMessageBox::Discard:
        event->accept();
        return;

      default:    // "Cancel"
        event->ignore();
        return;
    }
}
