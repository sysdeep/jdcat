#-------------------------------------------------
#
# Project created by QtCreator 2019-04-15T13:58:43
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app


CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    AddVolumeModal.cpp

HEADERS += \
        MainWindow.hpp \
    AddVolumeModal.hpp

FORMS += \
        MainWindow.ui \
    AddVolumeModal.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../appdb/release/ -lappdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../appdb/debug/ -lappdb
else:unix:!macx: LIBS += -L$$OUT_PWD/../appdb/ -lappdb

INCLUDEPATH += $$PWD/../appdb
DEPENDPATH += $$PWD/../appdb

RESOURCES += \
    rc.qrc
