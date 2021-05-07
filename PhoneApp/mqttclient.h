#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <qmqtt.h>

class MqttClient
{
public:
    MqttClient();
    void InitMqtt(QMQTT::Client *mqtt_client);
    void ConnectToMqtt(QMQTT::Client *mqtt_client);
    void DisConnectToMqtt(QMQTT::Client *mqtt_client);
};

#endif // MQTTCLIENT_H
