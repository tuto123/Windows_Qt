#include "mainwindow.h"
#include <QApplication>

#include "lockscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
    MainWindow w;
    w.setWindowTitle("Home");
    w.show();
#endif

    LockScreen *ls = new LockScreen();
    ls->setWindowTitle("LockScreen");
    ls->show();

    return a.exec();
}
