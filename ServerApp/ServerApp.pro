#-------------------------------------------------
#
# Project created by QtCreator 2021-04-26T16:47:47
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mqttclient.cpp

HEADERS  += mainwindow.h \
    mqttclient.h \
    database.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD//inc/mqtt
LIBS += $$PWD/libs/mqtt/libQt5Qmqtt.a    \
        $$PWD/libs/mqtt/libQt5Qmqttd.a

RESOURCES += \
    background.qrc
