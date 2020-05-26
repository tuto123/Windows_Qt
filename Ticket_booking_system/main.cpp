#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QTranslator>

#include "database.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(connectdatabase("flight_book_system"))
    {
        qDebug() << "Connect database Success!";
    }
    else
    {
        QMessageBox::about(NULL, "提示", "无法连接到数据库");
        return 1;
    }

    MainWindow w;
    w.setWindowTitle("航空机票预订系统");
    w.show();

    return a.exec();
}
