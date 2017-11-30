
//GROUP 3
/*Team Memebers:
-Hector Rios
-Eric J. Smrkovsky
-Freddie Martinez
-Joshua L. Douglas
-Aaron O. Gomez
-Scott D. Farrow*/
//You have to download the mulimedia files to run this program
//TYPE THIS INTO TERMINAL TO INCLUDE MULTIMEDIA FILE/PACKAGE:
// $ sudo apt-get install qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5
//Space bar is to fire
//Up controls speed
//Left and Right changes direction of the ship
//There is 5 levels
//Bullets have firing sound and asteroids make an explosion sound when hit.


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

/*| = - = - = D O C U M E N T A T I O N = - = - = |

========= |GAME FLOW|






     *******************************************************************
     *                      MainWindow                                 *
     *                                                                 *
     *                                                                 *
     *******************************************************************
                             ^
                             *calls
     *******************************************************************
     *                      Main                                       *
     *                                                                 *
     * create main event loop handler and parse command line arguments *
     *******************************************************************







========= |HEADERS|

= mainwindow.h = -

= scene.h = -

= station.h = -

= commandstationadd.h = -

= commandstationmove.h = -

= commandstationdelete.h = -

= playership.h = -

========= |SOURCES|

= main.cpp = -

= mainwindow.cpp = -

= scene.cpp = -

= station.cpp = -

= playership.cpp = -

========= |Variable|

= main.cpp = -

= mainwindow.cpp = -

= scene.cpp = -

= station.cpp = -

= playership.cpp = -


*/
