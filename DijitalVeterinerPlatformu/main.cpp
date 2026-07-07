#include "mainwindow.h"

#include <QApplication>

#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!DataBase::initialize()){
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}