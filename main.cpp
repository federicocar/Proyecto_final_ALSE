#include "mainwindow.h"
#include <stdlib.h>
#include <sqlite3.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
