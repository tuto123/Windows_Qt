#include "mainwindow.h"
#include "ui_mainwindow.h"

/*--------------------------Include Files--------------------------*/
#include <mqttclient.h>
extern  "C"
{
    #include "tea.h"
}
/*--------------------------Include Files--------------------------*/

/*--------------------------Local Define--------------------------*/
#define TEMP_ITEMID             0
#define HUMI_ITEMID             1
#define SOILHUMI_ITEMID         2
#define AIR_ITEMID              3
#define LIGHTISITY_ITEMID       4
#define FANSPEED_ITEMID         5
#define LIGHTSTATUS_ITEMID      6

#define ENV_TOPIC           "/Embedded/Terminal/device_env"
#define P2T_TOPIC_ENV       "/Phone/Terminal/device_env"
#define P2T_TOPIC_CTRL      "/Phone/Terminal/device_ctrl"
#define SPLITCHAR           "_"
#define HEADERSIZE          3
#define ENCRYPTKEY         "lifu123@outlook.com"
/*--------------------------Local Define--------------------------*/

/*--------------------------Local Data--------------------------*/
static QImage light_on;
static QImage light_off;
static QMQTT::Client mqttt_client;
static bool isDataBaseEmpty;
/*--------------------------Local Data--------------------------*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitShowData()
{
    ui->dial_FanSpeed->setEnabled(false);
    ui->light_checkBox->setEnabled(false);
}

//给界面添加可以缩放背景图片
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.setOpacity(0.9);          //背景图片透明度
    myPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/rec/img/phone_background.png"));
}

void MainWindow::onReceived(const QMQTT::Message &message)
{
    if(message.topic() == QString(ENV_TOPIC))
    {
        QString recieve_str = QString::fromUtf8(message.payload());
        qDebug() << "接收到的消息:" + recieve_str;
        ParseRecData(recieve_str);
    }
}

void MainWindow::PublishData(QString msgpay)
{
    QMQTT::Message msg;

    msg.setQos(0);
    msg.setTopic(P2T_TOPIC_CTRL);
    msg.setPayload(msgpay.toUtf8());
    mqttt_client.publish(msg);
}

void MainWindow::on_dial_FanSpeed_valueChanged(int value)
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
    PublishData(fanSpeed);
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

void MainWindow::on_pushButton_ConnectServer_clicked()
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

                ui->pushButton_ConnectServer->setText("断开服务器");
                ui->dial_FanSpeed->setEnabled(true);
                ui->light_checkBox->setEnabled(true);

                ui->label_ConnectServer->setText("连接服务器成功");

            }
        }
        else
        {
            ui->dial_FanSpeed->setEnabled(false);
            ui->light_checkBox->setEnabled(false);
            ui->pushButton_ConnectServer->setText("连接服务器");
            ui->label_ConnectServer->setText("未连接到服务器");
            QMessageBox::about(NULL, "提示", "已断开服务器连接");
            DisConnectMqtt();
        }
}

bool MainWindow::ConnectMqtt()
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
        QMessageBox::about(NULL, "提示", "服务器未连接!");
    }
    else
    {
        QMessageBox::about(NULL, "提示", "服务器连接成功!");
        QObject::connect(&mqttt_client,&QMQTT::Client::received, this, &MainWindow::onReceived);
    }
    return ret;
}

void MainWindow::DisConnectMqtt()
{
    MqttClient *mc = new MqttClient();
    mc->DisConnectToMqtt(&mqttt_client);
}

int MainWindow::CalculateItemNum(QString maskNum)
{
    return qCeil(qLn(maskNum.toInt() + 1)/qLn(2));
}

void MainWindow::on_light_checkBox_clicked()
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
        PublishData(lightStatus);
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
        PublishData(lightStatus);
    }
}

