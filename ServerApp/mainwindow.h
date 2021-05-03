#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*--------------------------Include Files--------------------------*/
#include "mqttclient.h"
/*--------------------------Include Files--------------------------*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *event);
    void ConnectMqtt();
    void DisConnectMqtt();
    void onReceived(const QMQTT::Message &message);
    void ParseRecData(QString recieve_str);
    int CalculateItemNum(QString maskNum);
    QString HashValue(QString srcData);
    void CheckDataBaseIsEmpty(QString dataBase);
    QString getDateTime();
    void AddDataBaseFirstData(QString srcData, QList<QString> headerDataList, QList<QString> itemIdList, QList<QString> itemDataList);
    void AddDataBaseData(QString srcData, QList<QString> headerDataList, QList<QString> itemIdList, QList<QString> itemDataList);
};

#endif // MAINWINDOW_H
