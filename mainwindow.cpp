#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"
#include "enemy.h"
#include "bullet.h"
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
#include <QtMath>
#include <QList>

#include <QUndoStack>
#include <QUndoView>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDateTime>
#include <QCloseEvent>
#include <QMessageBox>
#include <QToolBar>

//QList<Enemy*> AstList;
//QList<Bullet*> BullList;

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


//This creates the game (level) when new is pressed.
//It adds the essentials to the scene
// and connects important functions to the Timer.
bool MainWindow::gameState(int level)
{
    timer = new QTimer();       //Creating a new timer.
    player = new myRect(timer); //Creating player, and passing a Timer.

    //Add player to the scene.
    m_scene->addItem(player);

    //Set player in the middle.
    player->setPos(800 / 2, 600/ 2); //Set player in the middle.

    //Spawns # amount of enemies based (eventually) on level.
    spawnEnemy(10);

    //Connect timer to player movement(), so player can move.
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(movement()));

    //Connect timer to bullet creation, so bullet can move.
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(spawnBullet()));

    //Start the timer to go of every 30-ish seconds.
    timer->start(1000/33);

    return true;
}

//Spawns certain enemies. Enemy Creation.
void MainWindow::spawnEnemy(int limit)
{
    int count; //Loop counter,

    //Creates enemy depending on the limit given.
    for (count = 0; count < limit; count++)
    {
        //qDebug() << "Enemy being made...";
        //qDebug() << "Count: " << count;
        Enemy * enemy = new Enemy();
        AstList.insert(count, enemy);//Adds enemy to list use subscript value to access later.
        m_scene->addItem(enemy);     //Adds enemy to the scene.

        //Connects astroid movement to the Timer.
        QObject::connect(timer, SIGNAL(timeout()), enemy, SLOT(move()));
    }
    qDebug() << "Within Creating Enemy func.";
}

//This creates a bullet.
void MainWindow::spawnBullet()
{
    int count; //List counter.

    //Conveys player's position information to the bullet.
    float angle = player->giveAngle(),
          move_x = player->giveSpeedX(),
          move_y = player->giveSpeedY();

    if (player->returnSpacePressed())
    {
        Bullet * bullet = new Bullet(); //Makes a new Bullet.

        count = BullList.size();        //Checks size of bullet list
        count++;                        //Moves counter to next position
        BullList.insert(count, bullet); //Adds bullet to list using subscript value to access later.

        qDebug() << "BULLIST last: " << BullList.last()->giveExistance();
        //qDebug() << "x: " << (player->x() + player->giveSpeedX()) << " y: " << (player->y() - player->giveSpeedY());

        //Sets position of bullet, and then updates angle and (stacked) speed.
        bullet->setPos((player->x() + player->giveWidth()), (player->y()));
        bullet->updateBullet(angle, move_x, move_y);

        //Adds created Bullet to the Scene.
        m_scene->addItem(bullet);

        //Connects movement of bullet to the Timer.
        QObject::connect(timer, SIGNAL(timeout()), bullet, SLOT(move()));
    }

}

//This would remove both astroid and bullet
//from the scene, but not delete it.
//The list is for that.
void MainWindow::collisionItems()
{
    /*QList<QGraphicsItem *> colliding_items = collidingItems();
    for (count = 0, n = colliding_items.size(); count < n ;++count)
    {
        if (typeid(*(colliding_items[count])) == typeid(Enemy))
        {
            //Remove both*
            scene()->removeItem(colliding_items[count]);
            scene()->removeItem(this);

            //Freeing up memory used by deleted objects
            delete colliding_items[count];
            delete this;
            return;
        }
    }*/
}

/*********************************** showMessage ************************************/
void  MainWindow::showMessage( QString msg )
{
    //display message on main window status bar
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

void MainWindow::printWhenPressed()
{
    if(player->returnSpacePressed())
    {
        qDebug() << "Hello.";
    }
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
}*/


void  MainWindow::fileNew()
{
  bool current_state;
  m_undoStack->clear();
  Scene*          newScene = new Scene( m_undoStack );
  QGraphicsView*  view     = dynamic_cast<QGraphicsView*>( centralWidget() );
  view->setScene( newScene );
  delete m_scene;             //Delete old scene.
  m_scene = newScene;         //Create a new scene.

  //Sets up the view.
  view->setAlignment( Qt::AlignLeft | Qt::AlignTop );
  view->setFrameStyle( 0 );
  setCentralWidget( view );
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->show();
  view->setFixedSize(800, 600);//Set the view to a fixed size.

  current_state = gameState(2);//Creates a new game state.
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
