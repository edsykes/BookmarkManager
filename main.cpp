#include "View/mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.initTreeView();
    return a.exec();
}
