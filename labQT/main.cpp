#include <iostream>
#include "gui.h"
#include "tests.h"
#include "ui.h"
#include <qapplication.h>
#include <QWidget>

int main(int argc, char* argv[])
{
    //runTests();
    //RepoAparts repoAparts;
    RepoFile repoAparts{ "repo.txt" };
    //RepoLab repoAparts(0.3);
    RepoAparts repoList;
    Validator validator;
    ServiceAparts serviceAparts{ repoAparts, validator };
    ServiceList serviceList{ repoAparts, repoList ,validator };
    UI ui{ serviceAparts, serviceList };
    /*ui.run();
    return 0;*/
    QApplication a(argc, argv);
    mainGUI gui(serviceAparts, serviceList);
    gui.show();
    return a.exec();
}
