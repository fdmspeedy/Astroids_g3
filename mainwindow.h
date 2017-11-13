#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Scene;
class QUndoStack;
class QUndoView;
class QPrinter;

//class QAction;

#include <QMainWindow>

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

    //Maybe put in animation control.
    float buildVelocity_X();
    float buildVelocity_y();


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

protected:
  void closeEvent( QCloseEvent* );    // check if user really wants to exit

private:
    Ui::MainWindow *ui;
    Scene* m_scene;
    QUndoStack * m_undoStack;           // undo stack for undo & redo of commands
    QUndoView * m_undoView;            // undo stack window to view undo & redo commands
    bool new_game = false;

    //Maybe put in animation control.
    float Velocity_X[];
    float Velocity_Y[];

};

#endif // MAINWINDOW_H
