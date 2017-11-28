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

namespace Ui
{
class MainWindow;
}

/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

//This class runs the show/game.
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    //This controls the game flow. Recontruction Begins here.
    bool gameState(int);
    void spawnEnemy(int, char, float, float);
    void checkListItem();
    ~MainWindow();

public slots:
  void showMessage( QString );        // show message on status bar
  void showUndoStack();               // open up undo stack window
  void fileNew();                     // start new simulation
  bool fileSaveAs();                  // save simulation to file returning true if successful
  bool fileOpen();                    // load simulation file returning true if successful
  //void filePrintPreview();            // display print preview dialog
  //void filePrint();                   // display print dialog
  //void print( QPrinter* );            // draw print page
  void printWhenPressed();
  void spawnBullet();
  void collisionItems();
  void determineBreakUp();
  void isLevelDone();

protected:
  void closeEvent( QCloseEvent* );    // check if user really wants to exit

private:
    Ui::MainWindow *ui;
    Scene* m_scene;
    QUndoStack * m_undoStack;           // undo stack for undo & redo of commands
    QUndoView * m_undoView;            // undo stack window to view undo & redo commands

    int level_count;         //For the creation of enemies for certain levels.
    int current_level_count; //Saves the current level's count.
    bool gamechange;         //To determine if new level needed.

    QTimer * timer;
    myRect * player;

    QList<Enemy*> AstList;
    QList<Bullet*> BullList;

    float enemyPosX;
    float enemyPosY;

    char modeType;
    float enemy_x;
    float enemy_y;
};

#endif // MAINWINDOW_H
