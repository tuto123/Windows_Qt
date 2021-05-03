#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QtCore/qmath.h>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QPainter>

/*--------------------------Include Files--------------------------*/

/*--------------------------Include Files--------------------------*/

/*--------------------------Local Define--------------------------*/
#define ENV_TOPIC       "/Embedded/Terminal/device_env"
#define SPLITCHAR       "_"
#define HEADERSIZE      3
#define DATATABLENAME   "terminal_recv_data"
/*--------------------------Local Define--------------------------*/

/*--------------------------Local Data--------------------------*/
static QMQTT::Client mqttt_client;
static bool isDataBaseEmpty;
/*--------------------------Local Data--------------------------*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ConnectMqtt();
    CheckDataBaseIsEmpty(DATATABLENAME);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//给界面添加可以缩放背景图片
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.setOpacity(0.9);          //背景图片透明度
    myPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/rec/img/show_data_background.png"));
}

void MainWindow::ConnectMqtt()
{
    bool ret = false;

    MqttClient *mc = new MqttClient();
    mc->ConnectToMqtt(&mqttt_client);

    qDebug() << mqttt_client.host();
    qDebug() << mqttt_client.port();
    qDebug() << mqttt_client.clientId();
    qDebug() << mqttt_client.username();
    qDebug() << mqttt_client.password();

    QEventLoop eventloop;
    QTimer::singleShot(10, &eventloop, SLOT(quit()));
    eventloop.exec();

    ret = mqttt_client.isConnectedToHost();
    mqttt_client.subscribe(QString(ENV_TOPIC), 0);
    if(ret == false)
    {
        qDebug() << QString("服务器未连接!");
    }
    else
    {
        qDebug() << QString("服务器连接成功!");
        QObject::connect(&mqttt_client,&QMQTT::Client::received, this, &MainWindow::onReceived);
    }
}

void MainWindow::DisConnectMqtt()
{
    MqttClient *mc = new MqttClient();
    mc->DisConnectToMqtt(&mqttt_client);
}


void MainWindow::onReceived(const QMQTT::Message &message)
{
    QString recieve_str = QString::fromUtf8(message.payload());
    qDebug() << "接收到的消息:" + recieve_str;
    ParseRecData(recieve_str);
}

void MainWindow::ParseRecData(QString recieve_str)
{
    QString terminalId;
    QString deviceId;
    QString maskNum;

    QList<QString> parseDataList;
    QList<QString> headerDataList;
    QList<QString> itemIdList;
    QList<QString> itemDataList;

    parseDataList = recieve_str.split(SPLITCHAR);

    int i;
    for(i = 0; i < HEADERSIZE; i++)
    {
        headerDataList.append(parseDataList[i]);
    }
    terminalId = headerDataList[0];
    deviceId = headerDataList[1];
    maskNum = headerDataList[2];

    qDebug() << terminalId;
    qDebug() << deviceId;
    qDebug() << maskNum;

    int itemNum = 0;
    int maxPosition;
    maxPosition = CalculateItemNum(maskNum);

    for(i = 0; i < maxPosition; i++)
    {
        if((maskNum.toInt() & (int)pow(2, i)) == pow(2, i))
        {
            itemIdList.append(QString::number(i));
            itemNum++;
        }
    }

    for(i = 0; i < itemNum; i++)
    {
        itemDataList.append(parseDataList[i + 3]);
    }

    for(i = 0; i < itemNum; i++)
    {
        qDebug() << "item" + itemIdList[i] + ":" + itemDataList[i];
    }

    if(isDataBaseEmpty == true)
    {
        AddDataBaseFirstData(recieve_str, headerDataList, itemIdList, itemDataList);
    }
    else if(isDataBaseEmpty == false)
    {
        AddDataBaseData(recieve_str, headerDataList, itemIdList, itemDataList);
    }

}

int MainWindow::CalculateItemNum(QString maskNum)
{
    return qCeil(qLn(maskNum.toInt() + 1)/qLn(2));
}

QString MainWindow::getDateTime()
{
    QDateTime local(QDateTime::currentDateTime());
    QString localdatetime = local.toString("yyyy-MM-dd hh:mm:ss");

    return localdatetime;
}

void MainWindow::AddDataBaseFirstData(QString srcData, QList<QString> headerDataList, QList<QString> itemIdList, QList<QString> itemDataList)
{
    QString terminalId;
    QString deviceId;
    QString dateTime;

    terminalId = headerDataList[0];
    deviceId = headerDataList[1];
    dateTime = getDateTime();

    QString hashValue;
    QString zeroValue = "lifu123@outlook.com";
    hashValue = zeroValue + srcData;
    hashValue = HashValue(hashValue);

    qDebug() << srcData;
    qDebug() << terminalId;
    qDebug() << deviceId;
    qDebug() << dateTime;
    qDebug() << hashValue;

    QString query_str = QString("insert into terminal_recv_data(terminal_id, device_id, recv_time, recv_data, hash_data) \
                                    values('%1', '%2', '%3', '%4', '%5')")
                                    .arg(terminalId.toUtf8().data())
                                    .arg(deviceId.toUtf8().data())
                                    .arg(dateTime.toUtf8().data())
                                    .arg(srcData.toUtf8().data())
                                    .arg(hashValue.toUtf8().data());

    QSqlQuery query;
    if(query.exec(query_str))
    {
        qDebug() << "add first terminal_recv_data info successful!";
        printf("\nadd first terminal_recv_data info successful!");
    }
    else
    {
        qDebug() << "add first blockchain_info fail!";
        printf("\nadd first blockchain_info fail!");
    }

    for(int i = 0; i < itemDataList.size(); i++)
    {
        QString query_str1 = QString("update terminal_recv_data set item%1='%2' "
                                                      "where recv_time = '%3'")
                                                    .arg(itemIdList[i].toUtf8().data())
                                                    .arg(itemDataList[i].toUtf8().data()).arg(dateTime.toUtf8().data());

        QSqlQuery query1;
        if(query1.exec(query_str1))
        {
            qDebug() << "add first terminal_recv data successful!";
            printf("\nadd first terminal_recv data successful!");
        }
        else
        {
            qDebug() << "add first terminal_recv data fail!";
            printf("\nadd first terminal_recv data fail!");
        }
     }
}

void MainWindow::AddDataBaseData(QString srcData, QList<QString> headerDataList, QList<QString> itemIdList, QList<QString> itemDataList)
{
    QSqlTableModel terminalRecvDatamodel;
    terminalRecvDatamodel.setTable("terminal_recv_data");
    terminalRecvDatamodel.select();
    int rowcount = terminalRecvDatamodel.rowCount() - 1;
    QString preHashValue = terminalRecvDatamodel.data(terminalRecvDatamodel.index(rowcount, 4)).toString();

    QString hashValue;
    hashValue = preHashValue + srcData;
    hashValue = HashValue(hashValue);

    QString terminalId;
    QString deviceId;
    QString dateTime;

    terminalId = headerDataList[0];
    deviceId = headerDataList[1];
    dateTime = getDateTime();

    QString query_str = QString("insert into terminal_recv_data(terminal_id, device_id, recv_time, recv_data, hash_data) \
                                    values('%1', '%2', '%3', '%4', '%5')")
                                    .arg(terminalId.toUtf8().data())
                                    .arg(deviceId.toUtf8().data())
                                    .arg(dateTime.toUtf8().data())
                                    .arg(srcData.toUtf8().data())
                                    .arg(hashValue.toUtf8().data());

    QSqlQuery query;
    if(query.exec(query_str))
    {
        printf("\nadd terminal_recv_data info successful!");
    }
    else
    {
        printf("\nadd blockchain_info fail!");
    }

    for(int i = 0; i < itemDataList.size(); i++)
    {
        QString query_str1 = QString("update terminal_recv_data set item%1='%2' "
                                                      "where recv_time = '%3'")
                                                    .arg(itemIdList[i].toUtf8().data())
                                                    .arg(itemDataList[i].toUtf8().data()).arg(dateTime.toUtf8().data());

        QSqlQuery query1;
        if(query1.exec(query_str1))
        {
            printf("\nadd terminal_recv data successful!");
        }
        else
        {
            printf("\nadd terminal_recv data fail!");
        }
     }
}

QString MainWindow::HashValue(QString srcData)
{
    QString hashValue;
    hashValue.prepend(QCryptographicHash::hash(srcData.toUtf8(), QCryptographicHash::Md5).toHex());
    return hashValue;
}

void MainWindow::CheckDataBaseIsEmpty(QString tableName)
{
    QSqlTableModel clockchain_info_model;
    clockchain_info_model.setTable(tableName);
    clockchain_info_model.select();
    int rowcount = clockchain_info_model.rowCount();
    if(rowcount == 0)
    {
        isDataBaseEmpty = true;
    }
    else
    {
        isDataBaseEmpty = false;
    }
}

