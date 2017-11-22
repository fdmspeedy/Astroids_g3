
#include <QApplication>

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

    return a.exec();
}
