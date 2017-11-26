/*Team Memebers:
-Freddie Martinez
-Joshua L. Douglas
-Aaron O. Gomez
-Hector Rios
-Eric J. Smrkovsky
-Scott D. Farrow*/

#include <QApplication>
#include <QtGui>
#include <QPushButton>
#include "mainwindow.h"
#include "scene.h"

//This is up to step 6, including step 6.
int main(int argc, char *argv[])
{
    // create main event loop handler and parse command line arguments
    QApplication a(argc, argv);


    // create application main window & enter main event loop
    MainWindow window;
    window.show();

    //Ask to start game
    //QPushButton *newGameButton = new QPushButton("NEW GAME");
    //QObject::connect(newGameButton, SIGNAL(clicked()), &a, SLOT(fileNew()));
    //newGameButton->show();
    return a.exec();
}
