#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QWidget>
#include <QPainter>

#include <qmqtt.h>

namespace Ui {
class ShowData;
}

class ShowData : public QWidget
{
    Q_OBJECT

public:
    explicit ShowData(QWidget *parent = 0);
    ~ShowData();

private slots:
    void paintEvent(QPaintEvent *event);

    void setqssstyle(const QString &qssFile);

    void on_Home_clicked();

    void on_dial_FanSpeed_valueChanged(int value);

    void on_pushButton_ConnectServer_clicked();

    void on_pushButton_UpdateData_clicked();

    void on_pushButton_previousPage_clicked();

    void on_pushButton_nextPage_clicked();

    void on_pushButton_ReceiveData_clicked();

    void on_light_checkBox_clicked();


private:
    Ui::ShowData *ui;

    bool OpenSerialPort();
    bool ConnectMqtt();

    void serialPortRead();
    void InitShowData();
    void InitSerialPort();
    void DisConnectMqtt();
    void FindSerialPort();
    void PublishData(QString msgpay);
    void ParseRecData(QString recieve_str);
    int  CalculateItemNum(QString maskNum);
    void onReceived(const QMQTT::Message &message);
};

#endif // SHOWDATA_H
