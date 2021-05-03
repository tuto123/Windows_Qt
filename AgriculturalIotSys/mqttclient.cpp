#include "mqttclient.h"

#include <QTimer>

#define SERVERADDR  "192.168.222.128"
#define PORT        "1883"
#define CLIENTID    "terminal1"
#define USERTNAME   "allen"
#define PASSWORD    "123"

static QTimer mqtt_timer;

MqttClient::MqttClient()
{

}

void MqttClient::ConnectToMqtt(QMQTT::Client *mqtt_client)
{
    QHostAddress serveraddress;
    serveraddress = QHostAddress(QString(SERVERADDR));

    mqtt_client->setHost(serveraddress);
    mqtt_client->setPort(QString(PORT).toInt());
    mqtt_client->setClientId(QString(CLIENTID));
    mqtt_client->setUsername(QString(USERTNAME));
    mqtt_client->setPassword(QString(PASSWORD).toUtf8());
    mqtt_client->setAutoReconnect(true);
    mqtt_client->setCleanSession(true);
    mqtt_client->connectToHost();
}

void MqttClient::DisConnectToMqtt(QMQTT::Client *mqtt_client)
{
    mqtt_client->disconnectFromHost();

}
