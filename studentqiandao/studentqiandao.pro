#-------------------------------------------------
#
# Project created by QtCreator 2020-02-06T16:24:44
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = studentqiandao
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    singalstudent.cpp \
    login.cpp \
    zhuche.cpp

HEADERS  += widget.h \
    singalstudent.h \
    login.h \
    zhuche.h

FORMS    += widget.ui \
    singalstudent.ui \
    login.ui \
    zhuche.ui

RESOURCES += \
    qs/qss.qrc \
    qss1/qs1.qrc

DISTFILES +=
