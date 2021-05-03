#-------------------------------------------------
#
# Project created by QtCreator 2021-04-25T17:00:59
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AgriculturalIotSys
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    showdata.cpp \
    lockscreen.cpp \
    mqttclient.cpp

HEADERS  += mainwindow.h \
    showdata.h \
    lockscreen.h \
    mqttclient.h

FORMS    += mainwindow.ui \
    showdata.ui \
    lockscreen.ui

INCLUDEPATH += $$PWD//inc/mqtt
LIBS += $$PWD/libs/mqtt/libQt5Qmqtt.a    \
        $$PWD/libs/mqtt/libQt5Qmqttd.a

RESOURCES += \
    background.qrc
