#include "mainwindow.h"
#include "database.h"
#include "owner.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!DataBase::initialize()) {
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}