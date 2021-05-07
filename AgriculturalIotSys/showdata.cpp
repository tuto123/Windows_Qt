#include "showdata.h"
#include "ui_showdata.h"

extern  "C"
{
    #include "tea.h"
}

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QTimer>
#include <QImage>
#include <QString>
#include <QtCore/qmath.h>

/*--------------------------Include Files--------------------------*/
#include "mainwindow.h"
#include "lockscreen.h"
#include "mqttclient.h"
/*--------------------------Include Files--------------------------*/

/*--------------------------Data Format Definition--------------------------*/
/*Temperature:50
 *Humidity:30
 *LightIntensity:60
 *AirQuality:70
 *FanSpeed:80
 *LightStatus:1
 *
 *DeviceId_TerminalId_MaskNum_Temperature_Humidity_LightIntensity_AirQuality_FanSpeed_LightStatus
 *1_1_63_50_30_60_70_80_1
 *
 *
 *
 * /
/*--------------------------Data Format Definition--------------------------*/

/*--------------------------Local Define--------------------------*/
#define TEMP_ITEMID             0
#define HUMI_ITEMID             1
#define SOILHUMI_ITEMID         2
#define AIR_ITEMID              3
#define LIGHTISITY_ITEMID       4
#define FANSPEED_ITEMID         5
#define LIGHTSTATUS_ITEMID      6

#define SPLITCHAR               "_"
#define HEADERSIZE              3

#define SEND_TEST_DATA      "1_1_63_50_30_60_70_80_1"
#define RECV_TEST_DATA1     "1_1_63_50_30_60_70_80_1"
#define RECV_TEST_DATA2     "1_1_45_30_60_80_1"
#define RECV_TEST_DATA3     "2_1_22_70_60_33"
#define P2T_TOPIC_ENV       "/Phone/Terminal/device_env"
#define P2T_TOPIC_CTRL      "/Phone/Terminal/device_ctrl"
#define TERNIMAL_TOPIC      "/Server/Terminal/terminal_info"
#define ENV_TOPIC           "/Embedded/Terminal/device_env"
#define ENCRYPTKEY          "lifu123@outlook.com"
/*--------------------------Local Define--------------------------*/

/*--------------------------Local Data--------------------------*/
static QImage light_on;
static QImage light_off;
static QMQTT::Client mqttt_client;
static QList<QString> serialportnamelist;
static QString serialportname;
static QTimer mqtt_timer;
static QSerialPort serial;
static int serialbaudRate = 115200;
static char cammon_onlight[] = "";
static char cammon_offlight[] = "";
/*--------------------------Local Data--------------------------*/

ShowData::ShowData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowData)
{
    ui->setupUi(this);

    InitShowData();

    QString qssFile = qssFile = ":/rec/qss/darkgray.css";
    setqssstyle(qssFile);
}

ShowData::~ShowData()
{
    delete ui;
}

void ShowData::setqssstyle(const QString &qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        QString PaletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(PaletteColor)));
        file.close();
    }
}

//给界面添加可以缩放背景图片
void ShowData::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.setOpacity(0.9);          //背景图片透明度
    myPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/rec/img/home_background.png"));
}

void ShowData::InitShowData()
{
    ui->dial_FanSpeed->setEnabled(false);
    ui->light_checkBox->setEnabled(false);
    ui->pushButton_UpdateData->setEnabled(false);

}

bool ShowData::ConnectMqtt()
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
    mqttt_client.subscribe(QString(P2T_TOPIC_CTRL), 0);
    if(ret == false)
    {
        QMessageBox::about(NULL, "提示", "服务器未连接!");
    }
    else
    {
        QMessageBox::about(NULL, "提示", "服务器连接成功!");
        QObject::connect(&mqttt_client,&QMQTT::Client::received, this, &ShowData::onReceived);
    }
    return ret;
}

void ShowData::DisConnectMqtt()
{
    MqttClient *mc = new MqttClient();
    mc->DisConnectToMqtt(&mqttt_client);
}

bool ShowData::OpenSerialPort()
{
    int ret = -1;
    InitSerialPort();
    ret = serial.open(QIODevice::ReadWrite);
    connect(&serial, &QSerialPort::readyRead, this, &ShowData::serialPortRead);
    return ret;
}

void ShowData::serialPortRead()
{
    QString getData;
    getData = QString::fromLocal8Bit(serial.readAll());

    if(getData.contains(QString(SPLITCHAR)))
    {
        qDebug() << "getData: " + getData;
        ParseRecData(getData);
        PublishData(getData);
    }
    else
    {
        qDebug() << "printf: " + getData;
    }

}

void ShowData::InitSerialPort()
{
    serial.setPortName(serialportname);
    serial.setBaudRate(serialbaudRate);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
}

void ShowData::FindSerialPort()
{
    //通过QSerialPortInfo查找可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        serialportnamelist.append(info.portName());
    }
    if(serialportnamelist.count() == 0)
    {
        QMessageBox::about(NULL, "提示", "未接入无线模块!");
    }
    serialportname = serialportnamelist.at(4);
    qDebug() << QString(serialportname);
    qDebug() << serialportnamelist;
}

void ShowData::on_Home_clicked()
{
    serial.close();
    if(ui->pushButton_ConnectServer->text() == "断开服务器")
    {
        DisConnectMqtt();
    }
    LockScreen *ls = new LockScreen();
    this->close();
    ls->setWindowTitle("LockScreen");
    ls->show();
}

void ShowData::on_dial_FanSpeed_valueChanged(int value)
{
    QJsonObject fanjson;
    QString fanSpeed;
    fanjson.insert("FanSpeed", QString::number(value).toInt());
    fanSpeed = QString(QJsonDocument(fanjson).toJson());
    fanSpeed += '\r';
#if 0
    QByteArray encyptFanSpeed;
    QByteArray decryptFanSpeed;
    uint16_t encryptSize;
    uint16_t decryptSize;
    uint16_t fanSpeedSize = fanSpeed.size();
    uint16_t encryptKeySize = QString(ENCRYPTKEY).size();
    uint8_t srcFanSpeed[fanSpeedSize];
    uint8_t encryptKey[encryptKeySize];

    for(int i = 0; i < fanSpeedSize; i++)
    {
        srcFanSpeed[i] = fanSpeed.toLatin1()[i];
    }
    for(int i = 0; i < encryptKeySize; i++)
    {
        encryptKey[i] = QString(ENCRYPTKEY).toLatin1()[i];
    }

    encryptSize = encrypt(srcFanSpeed, fanSpeedSize, encryptKey);
    for(int i = 0; i < encryptSize; i++)
    {
        encyptFanSpeed[i] = srcFanSpeed[i];
    }
    QString(encyptFanSpeed).append("\r").toLocal8Bit();
    qDebug() << "加密后数据:" + QString(encyptFanSpeed);

#if 0
    decryptSize = decrypt(srcFanSpeed, encryptSize, encryptKey);
    for(int i = 0; i < decryptSize; i++)
    {
        decryptFanSpeed[i] = srcFanSpeed[i];
    }
    qDebug() << "解密后数据:" + QString(decryptFanSpeed);
#endif
#endif
    ui->lcdNumber_FanSpeed->display(value);
    serial.write(fanSpeed.toLatin1());

}

void ShowData::onReceived(const QMQTT::Message &message)
{
    if(message.topic() == QString(P2T_TOPIC_CTRL))
    {
        QString recieve_str = QString::fromUtf8(message.payload());
        qDebug() << "手机的控制消息:" + recieve_str;
        serial.write(recieve_str.toLatin1());
    }
}

void ShowData::on_pushButton_ConnectServer_clicked()
{
    bool ret = false;

    if(ui->pushButton_ConnectServer->text() == "连接服务器")
    {
        ret = ConnectMqtt();
        if(ret == false)
        {

        }
        else
        {
            ui->dial_FanSpeed->setNotchesVisible(true);
            ui->dial_FanSpeed->setMinimum(1);
            ui->dial_FanSpeed->setMaximum(99);
            ui->dial_FanSpeed->setRange(1, 99);
            ui->dial_FanSpeed->setPageStep(5);

            FindSerialPort();
            ret = OpenSerialPort();
            if(ret == false)
            {
                QMessageBox::about(NULL, "提示", "初始化无线模块失败");
            }
            else
            {
                ui->pushButton_UpdateData->setEnabled(true);
                ui->pushButton_ConnectServer->setText("断开服务器");
                ui->dial_FanSpeed->setEnabled(true);
                ui->light_checkBox->setEnabled(true);
                qDebug() << QString("Init " + serialportname + " successful");
                ui->label_ConnectServer->setText("连接服务器成功");
            }
        }
    }
    else
    {
        ui->dial_FanSpeed->setEnabled(false);
        ui->light_checkBox->setEnabled(false);
        ui->pushButton_UpdateData->setEnabled(false);
        ui->pushButton_ConnectServer->setText("连接服务器");
        ui->label_ConnectServer->setText("未连接到服务器");
        QMessageBox::about(NULL, "提示", "已断开服务器连接");
        DisConnectMqtt();
        serial.close();
    }

}

void ShowData::on_light_checkBox_clicked()
{
    QJsonObject lightJson;
    QString lightStatus;

    if(ui->light_checkBox->checkState() == Qt::Checked)
    {
        qDebug() << "ui->light_checkBox->checkState() == Qt::Checked";
        light_on.load(":/rec/img/light_on.png");
        ui->device2_light_icon_label->setPixmap(QPixmap::fromImage(light_on));

        lightJson.insert("LightStat", QString::number(1).toInt());
        lightStatus = QString(QJsonDocument(lightJson).toJson());
        lightStatus += '\r';
#if 0
        QByteArray encyptLightStatus;
        QByteArray decryptLightStatus;
        uint16_t encryptSize;
        uint16_t decryptSize;
        uint16_t lightStatusSize = lightStatus.size();
        uint16_t encryptKeySize = QString(ENCRYPTKEY).size();
        uint8_t srcLightStatus[lightStatusSize];
        uint8_t encryptKey[encryptKeySize];

        for(int i = 0; i < lightStatusSize; i++)
        {
            srcLightStatus[i] = lightStatus.toLatin1()[i];
        }
        for(int i = 0; i < encryptKeySize; i++)
        {
            encryptKey[i] = QString(ENCRYPTKEY).toLatin1()[i];
        }

        encryptSize = encrypt(srcLightStatus, lightStatusSize, encryptKey);
        for(int i = 0; i < encryptSize; i++)
        {
            encyptLightStatus[i] = srcLightStatus[i];
        }
        qDebug() << "加密后数据:" + QString(encyptLightStatus);

#if 0
        decryptSize = decrypt(srcLightStatus, encryptSize, encryptKey);
        for(int i = 0; i < decryptSize; i++)
        {
            decryptLightStatus[i] = srcLightStatus[i];
        }
        qDebug() << "解密后数据:" + QString(decryptLightStatus);
#endif
#endif
        qDebug() << lightStatus;
        serial.write(lightStatus.toLatin1());
    }
    if (ui->light_checkBox->checkState() == Qt::Unchecked)
    {
        qDebug() << "ui->light_checkBox->checkState() == Qt::Unchecked";
        light_off.load(":/rec/img/light_off.png");
        ui->device2_light_icon_label->setPixmap(QPixmap::fromImage(light_off));

        lightJson.insert("LightStat", QString::number(0).toInt());
        lightStatus = QString(QJsonDocument(lightJson).toJson());
        lightStatus += '\r';
#if 0
        QByteArray encyptLightStatus;
        QByteArray decryptLightStatus;
        uint16_t encryptSize;
        uint16_t decryptSize;
        uint16_t lightStatusSize = lightStatus.size();
        uint16_t encryptKeySize = QString(ENCRYPTKEY).size();
        uint8_t srcLightStatus[lightStatusSize];
        uint8_t encryptKey[encryptKeySize];

        for(int i = 0; i < lightStatusSize; i++)
        {
            srcLightStatus[i] = lightStatus.toLatin1()[i];
        }
        for(int i = 0; i < encryptKeySize; i++)
        {
            encryptKey[i] = QString(ENCRYPTKEY).toLatin1()[i];
        }

        encryptSize = encrypt(srcLightStatus, lightStatusSize, encryptKey);
        for(int i = 0; i < encryptSize; i++)
        {
            encyptLightStatus[i] = srcLightStatus[i];
        }
        qDebug() << "加密后数据:" + QString(encyptLightStatus);

#if 0
        decryptSize = decrypt(srcLightStatus, encryptSize, encryptKey);
        for(int i = 0; i < decryptSize; i++)
        {
            decryptLightStatus[i] = srcLightStatus[i];
        }
        qDebug() << "解密后数据:" + QString(decryptLightStatus);
#endif
#endif
        qDebug() << lightStatus;
        serial.write(lightStatus.toLatin1());
    }
}

void ShowData::on_pushButton_UpdateData_clicked()
{
    QMQTT::Message msg;
    QByteArray msgpay;

    msg.setQos(0);
    msg.setTopic(ENV_TOPIC);
    msgpay = QString(SEND_TEST_DATA).toUtf8();
    msg.setPayload(msgpay);
    mqttt_client.publish(msg);

    msgpay = QString(RECV_TEST_DATA1).toUtf8();
    msg.setPayload(msgpay);
    mqttt_client.publish(msg);

    msgpay = QString(RECV_TEST_DATA2).toUtf8();
    msg.setPayload(msgpay);
    mqttt_client.publish(msg);

    msgpay = QString(RECV_TEST_DATA3).toUtf8();
    msg.setPayload(msgpay);
    mqttt_client.publish(msg);
}

void ShowData::PublishData(QString msgpay)
{
    QMQTT::Message msg;

    msg.setQos(0);
    msg.setTopic(ENV_TOPIC);
    msg.setPayload(msgpay.toUtf8());
    mqttt_client.publish(msg);
}

void ShowData::on_pushButton_previousPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void ShowData::on_pushButton_nextPage_clicked()
{
     ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void ShowData::on_pushButton_ReceiveData_clicked()
{
    ParseRecData(RECV_TEST_DATA1);
    ParseRecData(RECV_TEST_DATA2);
    ParseRecData(RECV_TEST_DATA3);
}

void ShowData::ParseRecData(QString recieve_str)
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
    deviceId = headerDataList[0];
    terminalId = headerDataList[1];
    maskNum = headerDataList[2];

    qDebug() << "terminalId: " + terminalId;
    qDebug() << "deviceId: " + deviceId;
    qDebug() << "maskNum: " + maskNum;

    int itemNum = 0;
    int maxPosition;
    maxPosition = CalculateItemNum(maskNum);
    qDebug() << "maxPosition: " + QString::number(maxPosition);
    for(i = 0; i < maxPosition; i++)
    {
        itemDataList.append(QString::number(0));
    }

    for(i = 0; i < maxPosition; i++)
    {
        if((maskNum.toInt() & (int)pow(2, i)) == pow(2, i))
        {
            itemIdList.append(QString::number(i));
            itemNum++;
        }
    }

    qDebug() << "终端" + terminalId + "的设备" + deviceId + "共有" + QString::number(itemNum) + "个测项";

    for(i = 0; i < itemNum; i++)
    {
        itemDataList.insert(itemIdList[i].toInt(), parseDataList[i + 3]);
    }

    for(i = 0; i < itemNum; i++)
    {
        qDebug() << "item" + itemIdList[i] + ":" + itemDataList[i];
    }

    qDebug() << itemIdList;
    qDebug() << itemDataList;

    if(itemIdList.contains(QString::number(TEMP_ITEMID)))
    {
        ui->lcdNumber_Temperture->display(itemDataList[TEMP_ITEMID]);
    }
    if(itemIdList.contains(QString::number(HUMI_ITEMID)))
    {
        ui->lcdNumber_Humidity->display(itemDataList[HUMI_ITEMID]);
    }
    if(itemIdList.contains(QString::number(SOILHUMI_ITEMID)))
    {
        ui->lcdNumber_Soil->display(itemDataList[SOILHUMI_ITEMID]);
    }
    if(itemIdList.contains(QString::number(AIR_ITEMID)))
    {
        ui->lcdNumber_Air->display(itemDataList[AIR_ITEMID]);
    }
    if(itemIdList.contains(QString::number(FANSPEED_ITEMID)))
    {
        ui->lcdNumber_FanSpeed->display(itemDataList[FANSPEED_ITEMID]);
    }
    if(itemIdList.contains(QString::number(LIGHTISITY_ITEMID)))
    {
        ui->lcdNumber_Light->display(itemDataList[LIGHTISITY_ITEMID]);
        if(itemDataList[LIGHTISITY_ITEMID].toInt() < 40)
        {
            light_on.load(":/rec/img/light_on.png");
            ui->device1_light_icon_label->setPixmap(QPixmap::fromImage(light_on));
        }
        else if(itemDataList[LIGHTISITY_ITEMID].toInt() >= 40)
        {
            light_off.load(":/rec/img/light_off.png");
            ui->device1_light_icon_label->setPixmap(QPixmap::fromImage(light_off));
        }
    }
    if(itemIdList.contains(QString::number(LIGHTSTATUS_ITEMID)))
    {
        if(itemDataList[LIGHTSTATUS_ITEMID].toInt() == 1 && (ui->light_checkBox->checkState() == Qt::Unchecked))
        {
            light_on.load(":/rec/img/light_on.png");
            ui->device2_light_icon_label->setPixmap(QPixmap::fromImage(light_on));

            ui->light_checkBox->setCheckState(Qt::Checked);


        }
        else if(itemDataList[LIGHTSTATUS_ITEMID].toInt() == 0 && (ui->light_checkBox->checkState() == Qt::Checked))
        {
            light_off.load(":/rec/img/light_off.png");
            ui->device2_light_icon_label->setPixmap(QPixmap::fromImage(light_off));

            ui->light_checkBox->setCheckState(Qt::Unchecked);
        }
    }

}

int ShowData::CalculateItemNum(QString maskNum)
{
    return qCeil(qLn(maskNum.toInt() + 1)/qLn(2));
}
