#-------------------------------------------------
#
# Project created by QtCreator 2020-05-14T10:16:23
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ticket_booking_system
TEMPLATE = app

RC_ICONS = my.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    userwindow.cpp \
    adminwindow.cpp

HEADERS  += mainwindow.h \
    userwindow.h \
    adminwindow.h \
    database.h

FORMS    += mainwindow.ui \
    userwindow.ui \
    adminwindow.ui

RESOURCES += \
    material.qrc
