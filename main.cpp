#include "mainwindow.h"
#include <QApplication>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
