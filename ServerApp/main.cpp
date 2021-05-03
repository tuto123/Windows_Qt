#include "mainwindow.h"
#include <QApplication>

#include "database.h"

#define DATABASENAME   "agriculture_sys"

int main(int argc, char *argv[])
{
    if(connectdatabase(DATABASENAME))
    {
        qDebug() << "======================================================";
        qDebug() << "connect database successfully!";
        qDebug() << "======================================================";
    }
    else
    {
        qDebug() << "======================================================";
        qDebug() << "can't connect database!";
        qDebug() << "======================================================";
        return 1;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Serverapp");
    w.show();

    return a.exec();
}
