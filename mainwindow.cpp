#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include "playerobject.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QAction>
#include <QStatusBar>
#include <QTimer>
#include <QDebug>

#include <QUndoStack>
#include <QUndoView>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDateTime>
//#include <QPrinter>
//#include <QPrintPreviewDialog>
//#include <QPrintDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QToolBar>

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

//Constructor. AKA most of the program is going to run here. I think.
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu*  fileMenu = menuBar()->addMenu( "&File" );

    // create file menu options
    QAction* newAction     = fileMenu->addAction( "&New", this, SLOT(fileNew()) );

    fileMenu->addSeparator();
    fileMenu->addAction( "&Quit", this, SLOT(close()) );
    newAction->setShortcut( QKeySequence::New );

    // create undo stack and associated menu actions
    m_undoStack = new QUndoStack( this );
    m_undoView  = 0;

    // create scene and central widget view of scene
    m_scene               = new Scene(m_undoStack);
    QGraphicsView*   view = new QGraphicsView( m_scene );
    view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    view->setFrameStyle( 0 );
    setCentralWidget( view );

    //Add player to scene
    //m_scene->addItem(player);

    //Regulate view-ing of the scene.
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(800, 600);//Set the view to a fixed size.
    m_scene->setSceneRect(0, 0, 800, 600);

    // connect message signal from scene to showMessage slot
    connect( m_scene, SIGNAL(message(QString)), this, SLOT(showMessage(QString)) );

    // add status bar message
    statusBar()->showMessage("QSimulate has started");
}

/*********************************** showMessage ************************************/
void  MainWindow::showMessage( QString msg )
{
  // display message on main window status bar
    statusBar()->showMessage( msg );
}

/*********************************** showUndoStack ***********************************/

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
  //m_scene->writeStream( &stream );
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
          qDebug() << "";//newScene->readStream( &stream );
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

/*void  MainWindow::filePrintPreview()
{
  // display print preview dialog
  QPrinter             printer( QPrinter::ScreenResolution ); // QPrinter::HighResolution );
  QPrintPreviewDialog  preview( &printer, this );
  connect( &preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)) );
  preview.exec();
}

/************************************ filePrint **************************************/

/*void  MainWindow::filePrint()
{
  // display print dialog and if accepted print
  QPrinter       printer( QPrinter::ScreenResolution );
  QPrintDialog   dialog( &printer, this );
  if ( dialog.exec() == QDialog::Accepted ) print( &printer );
}

/*************************************** print ***************************************/

/*void  MainWindow::print( QPrinter* printer )
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
  m_undoStack->clear();
  Scene*          newScene = new Scene( m_undoStack );
  QGraphicsView*  view     = dynamic_cast<QGraphicsView*>( centralWidget() );
  view->setScene( newScene );
  delete m_scene;
  m_scene = newScene;

  QTimer * timer = new QTimer();
  myRect *player = new myRect(timer); //Creating player, and passing a Timer.

  m_scene->addItem(player);
  //Set player in the middle.
  player->setPos(800 / 2, 600/ 2); //Set player in the middle.
  //Spawn Enemies
  //QTimer * timer = new QTimer();

  //player->updateLevel(2);

  QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));

  timer->start(1000/33); //Make an enemy every 2000 milli-seconds
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

MainWindow::~MainWindow()
{
    delete ui;
}
