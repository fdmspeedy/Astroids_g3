#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playerobject.h"
#include "enemy.h"
#include "bullet.h"

class Scene;
class QUndoStack;
class QUndoView;
class QPrinter;

//class QAction;

#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QMediaPlayer>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QFrame>


namespace Ui
{
class MainWindow;
}

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

//This class runs the show/game.
//It holds the recurring game states and important variables.
//The player, timer, and anything important is a private variable.
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QFrame *frame;
    QProgressBar *progressBar;
    int healthProg;
    explicit MainWindow(QWidget *parent = 0);

    //This controls the game flow. Recontruction Begins here.
    bool gameState(int);
    void spawnEnemy(int, char, float, float);
    ~MainWindow();

public slots: //Connected to the Timer.
  void showMessage( QString );        // show message on status bar
  void showUndoStack();               // open up undo stack window
  void fileNew();                     // start new simulation
  bool fileSaveAs();                  // save simulation to file returning true if successful
  bool fileOpen();                    // load simulation file returning true if successful

  //Determines when the player hit the space command bar and spawns a bullet.
  void spawnBullet();

  //Constantly checks if something has collided, and spawns of enemies when neeeded.
  void determineBreakUp();

  //This constantly checks if the level is over and starts the next game state.
  void isLevelDone();

protected:
  void closeEvent( QCloseEvent* );    // check if user really wants to exit

private:
    Ui::MainWindow *ui;

    //The scene is the data that the view projects.
    //Add things to the scene in order for them to appear on the screen.
    Scene* m_scene;
    QUndoStack * m_undoStack;           // undo stack for undo & redo of commands
    QUndoView * m_undoView;            // undo stack window to view undo & redo commands

    int level_count;         //For the creation of enemies for certain levels.
    int current_level_count; //Saves the current level's count of enemies.
    bool gamechange;         //To determine if a new level needed, or restarting back to level 1.

    QTimer * timer;          //Timer handles the timing of game objects and interactions.
    myRect * player;         //The User controlled item that serves as the player ship on screen.

    QList<Enemy*> AstList;   //Records Number/Type of Asteriods on Screen,
    QList<Bullet*> BullList; //Records Number/Type of Bullets on Screen,

    float enemyPosX;         //Records recently destroyed Asteroids X Position
    float enemyPosY;         //Records recently destroyed Asteroids Y Position

    char modeType;           //Starting Asteriods Size Type.
    float enemy_x;           //Records stacked speed of enemies
    float enemy_y;           //Records stacked speed of enemies

    QMediaPlayer * bulletSound; //sound for bullet
    QMediaPlayer * crashSound;  //sound for crash
    QMediaPlayer * levelSound;  //sound for new levels
};

#endif // MAINWINDOW_H
