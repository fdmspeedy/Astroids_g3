

/*Team Memebers:
-Hector Rios
-Eric J. Smrkovsky
-Freddie Martinez
-Joshua L. Douglas
-Aaron O. Gomez
-Scott D. Farrow*/

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
