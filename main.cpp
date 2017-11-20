//Asteroids Project
//Group 2
//Travis Walker
//Preston Moore
//Rohin Singh
//Edgar Gomez
//Khoa Truong
//Lal Angdembe
#include <QDesktopWidget>
#include <QApplication>
#include "scene.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
  //Seed random number generator
    srand(time(0));

  // create main event loop handler and parse command line arguments
    QApplication app(argc, argv);

  // create application main window & enter main event loop
    MainWindow window;
    QDesktopWidget dw;

  //window's size is fixed at 80% of the user's sceen size
    int x=dw.width()*0.8;
    int y=dw.height()*0.8;
    window.setFixedSize(x,y);

  //Show the window
    window.show();

    return app.exec();
}
