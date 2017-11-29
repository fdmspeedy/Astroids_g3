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
#include <typeinfo>
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

#include <QMediaPlayer>

#include <iostream>
using namespace std;

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

//Constructor. AKA most of the program is going to run here. I think.
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create file menu options
    QMenu*  fileMenu = menuBar()->addMenu( "&File" );

    QAction* newAction     = fileMenu->addAction( "&New", this, SLOT(fileNew()) );
    newAction->setShortcut( QKeySequence::New );

    fileMenu->addSeparator();
    QAction* OpenAction     = fileMenu->addAction( "&Open", this, SLOT(fileOpen()) );
    OpenAction->setShortcut( QKeySequence::Open );

    QAction* SaveAction     = fileMenu->addAction( "&Save", this, SLOT(fileSaveAs()) );
    SaveAction->setShortcut( QKeySequence::SaveAs );

    fileMenu->addSeparator();
    QAction* QuitAction     = fileMenu->addAction( "&Quit", this, SLOT(close()) );
    QuitAction->setShortcut( QKeySequence::Quit );



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

    frame = new QFrame(view);
    frame->setObjectName(QStringLiteral("frame"));
    frame->setGeometry(QRect(0, 410, 781, 51));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    progressBar = new QProgressBar(frame);
    progressBar->setObjectName(QStringLiteral("progressBar"));
    progressBar->setGeometry(QRect(350, 10, 118, 41));
    progressBar->setValue(healthProg);


    //connect(healthProg, SIGNAL(valuechanged(int))
    //        , progressBar, SLOT(setValue(int)));



    //void QProgressBar::valueChanged(int value)myRect::player_health

    modeType = 'B';
    enemy_x = 0.0;
    enemy_y = 0.0;

    level_count = 2;     // Amount of asteriods in starting level.
    gamechange = false;  //No new game at this point.

    //Play background music
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/files/BACKGROUND.mp3"));
    music->play();

    //Play sound when bullet is created
    bulletSound = new QMediaPlayer();
    bulletSound->setMedia(QUrl("qrc:/new/files/FIRE.mp3"));

    //Play sound when collision is detected
    crashSound = new QMediaPlayer();
    crashSound->setMedia(QUrl("qrc:/new/files/HIT.mp3"));

    //Play sound when starting new level
    levelSound = new QMediaPlayer();
    levelSound->setMedia(QUrl("qrc:/new/files/NEXTLEVEL.wav"));
}

void  MainWindow::fileNew()
{
  bool current_state;

  //Saves the current level count variable for the enemies in this 'level'.
  current_level_count = level_count;

  m_undoStack->clear();
  Scene*          newScene = new Scene( m_undoStack );
  QGraphicsView*  view     = dynamic_cast<QGraphicsView*>( centralWidget() );
  view->setScene( newScene );
  qDebug() << "Before deletion of old scene.";

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
  m_scene->setSceneRect(0, 0, 800, 600);

  AstList.clear();
  BullList.clear();

  if (gamechange)
  {
      current_state = gameState(level_count);//Creates a new game state.
      gamechange = false;
  }
  else
      current_state = gameState(current_level_count);//Creates a new game state.
}

//This creates the game (level) when new is pressed.
//It adds the essentials to the scene
// and connects important functions to the Timer.
bool MainWindow::gameState(int level)
{
    timer = new QTimer();       //Creating a new timer.
    player = new myRect(timer); //Creating player, and passing a Timer.

    int healthProg = player->giveHealth(); //set healthprog
    qDebug() << "HealthProg: " << healthProg;

    //Add player to the scene.
    m_scene->addItem(player);

    //Set player in the middle.
    player->setPos(800 / 2, 600/ 2); //Set player in the middle.

    //Spawns # amount of enemies based (eventually) on level.
    spawnEnemy(level, modeType, 0, 0);

    //Connect timer to player movement(), so player can move.
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(movement()));

    //Connect timer to bullet creation, so bullet can move.
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(spawnBullet()));

    //Find when something died, and create new enemies.
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(determineBreakUp()));

    //Determines when to start a new level.
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(isLevelDone()));

    //Start the timer to go of every 30-ish seconds.
    timer->start(1000/33);

    return true;
}

//Spawns certain enemies. Enemy Creation.
void MainWindow::spawnEnemy(int limit, char size, float before_x, float before_y)
{
    int count; //Loop counter,

    //Creates enemy depending on the limit given.
    for (count = 0; count < limit; count++)
    {
        qDebug() << "Spawn Enemy Entered Size: " << size;

        Enemy * enemy = new Enemy(size, before_x, before_y);
        AstList.insert(count, enemy);//Adds enemy to list use subscript value to access later.

        qDebug()<< "Just Added: " << AstList[count]->giveType();

        m_scene->addItem(enemy);     //Adds enemy to the scene.

        //qDebug() << "adress?: " << enemy;
        cout << "adress?: " << enemy << endl;

        //Connects astroid movement to the Timer.
        QObject::connect(timer, SIGNAL(timeout()), enemy, SLOT(move()));
    }
    qDebug() << "Within Creating Enemy func.";
}

void MainWindow::checkListItem()
{
    int countA, countB,
        current_list_len = BullList.size(),
        sceneCount, sceneItems = m_scene->items().size();

    //QList<QGraphicsPixmapItem *> OnScene = m_scene->items();

    /*for (sceneCount = 0; sceneCount < sceneItems; sceneCount++)
    {
        //qDebug() << "reference: " << *OnScene[sceneCount];
    }*/
    //for (countA = 0; countA < current_list_len; countA++)
}

//This creates a bullet.
void MainWindow::spawnBullet()
{
    int count; //List counter.

    //Conveys player's position information to the bullet.
    float angle = player->giveAngle(),
          move_x = player->giveSpeedX(),
          move_y = player->giveSpeedY();;

    QList <Bullet *> TempList;

    if (player->returnSpacePressed())
    {
        Bullet * bullet = new Bullet(); //Makes a new Bullet.

        //Play sound
        if(bulletSound->state() == QMediaPlayer::PlayingState)
        {
            bulletSound->setPosition(0);
        }
        else if(bulletSound->state() == QMediaPlayer::StoppedState)
        {
        bulletSound->play();
        }

        count = BullList.size();        //Checks size of bullet list
        count++;                        //Moves counter to next position
        BullList.insert(count, bullet); //Adds bullet to list using subscript value to access later.

        //Sets position of bullet, and then updates angle and (stacked) speed.
        //bullet->setPos((player->x() + player->giveWidth()), (player->y()));
        qDebug() << "player Y: " << player->y();
        qDebug() << "player height: " << player->giveHeight();

        bullet->setPos((player->x() + player->giveWidth()), (player->y()));// + player->giveHeight()));

        bullet->updateBullet(angle, move_x, move_y);

        //Adds created Bullet to the Scene.
        m_scene->addItem(bullet);

        //Connects movement of bullet to the Timer.
        QObject::connect(timer, SIGNAL(timeout()), bullet, SLOT(move()));


    }

    //Updates the Bullet List.
    for (count = 0; count < BullList.size(); count++)
    {
        if (BullList[count]->giveExistance() == true)
            TempList.append(BullList[count]);
    }
    BullList = TempList; //Update Bullet List.

}

void MainWindow::collisionItems()
{

}

//This determines where the astroid that collided is
//and then sets it to false and removes it from scene.
void MainWindow::determineBreakUp()
{
    int countA, AstListLen = AstList.size();
    float X, Y;
    char type;

    QList<Enemy *> enemyHit;
    QList<Enemy *> TempList;

    //Check for dead enemies. Then sends them to another list.
    for (countA = 0; countA < AstListLen; countA++)
    {
        if ((AstList[countA]->giveState()) == false)
            enemyHit.append(AstList[countA]);

        else if ((AstList[countA]->giveState()) == true)
            TempList.append(AstList[countA]);
    }

    AstList = TempList; //Update the AstList.

    //Going through what has just been hit.
    //Determine what they are and destroy/create new ones.
    if (enemyHit.size() != 0)
    {


        qDebug() << "Break 4";
        qDebug() << "size: " << enemyHit.size();

        for (countA = 0; countA < enemyHit.size(); countA++)
        {

            qDebug() << "Break 5";

            type = enemyHit.value(countA)->giveType();
            X = enemyHit.value(countA)->givePosX();
            Y = enemyHit.value(countA)->givePosY();

            qDebug() << "Break 6";

            //Play sound
            if(crashSound->state() == QMediaPlayer::PlayingState)
            {
                crashSound->setPosition(0);
            }
            else if(crashSound->state() == QMediaPlayer::StoppedState)
            {
            crashSound->play();
            }

            if (type == 'B')
                spawnEnemy(2, 'M', X, Y);
            else if (type == 'M')
                spawnEnemy(2, 'S', X, Y);

            qDebug() << "Break 7";

            delete enemyHit.value(countA);

        }
        qDebug() << "Break 8";

        //enemyHit.clear();
    }
}

//Checks when there are no Enemies and starts the new level.
//When 'limit' reached; it stops the increase in hardness.
void MainWindow::isLevelDone()
{
    //if all asteroids gone, start a new level.
    if (AstList.size() == 0)
    {
        level_count++;      //Increment the amount of enemies in next level.
        gamechange = true;  //New gamestate needed.

        if(level_count < 5)
        {
           //Play sound
           if(levelSound->state() == QMediaPlayer::PlayingState)
           {
               levelSound->setPosition(0);
           }
           else if(levelSound->state() == QMediaPlayer::StoppedState)
           {
           levelSound->play();
           }
        }
        if (level_count == 5)
        {
            //Levels done = end game.
            qDebug() << "Limit reached - End Game.";
        }
        else
        {
            fileNew();      //Start another game state

        }
    }
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
