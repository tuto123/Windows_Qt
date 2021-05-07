#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QtCore/qmath.h>
#include <QMessageBox>
#include <QPainter>

#include <qmqtt.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_dial_FanSpeed_valueChanged(int value);

    void on_pushButton_ConnectServer_clicked();

    void on_light_checkBox_clicked();

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *event);
    void InitShowData();

    bool ConnectMqtt();

    void DisConnectMqtt();
    void ParseRecData(QString recieve_str);
    void onReceived(const QMQTT::Message &message);
    void PublishData(QString msgpay);
    int  CalculateItemNum(QString maskNum);
};

#endif // MAINWINDOW_H
