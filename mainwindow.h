#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Scene;

#include <QMainWindow>
/*************************************************************************************/
/*********************** Main application window for QSimulate ***********************/
/*************************************************************************************/

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow(); // constructor

public slots:
  void showMessage( QString ); // show message on status bar
  void startGame();

private:
  Scene* m_scene; // scene representing the simulated landscape
};

#endif  // MAINWINDOW_H
