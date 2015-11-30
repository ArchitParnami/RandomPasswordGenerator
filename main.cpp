#include <QtGui/QApplication>
#include "rpg.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RPG w;
    w.show();    
    return a.exec();
}
