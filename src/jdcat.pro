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
    gui/FilesListNavigator.cpp \
    gui/modals/EditVolumeModal.cpp \
    gui/FilesList.cpp \
    gui/VolumesList.cpp \
    gui/modals/FaconModal.cpp \
        main.cpp \
        gui/MainWindow.cpp \
        gui/AddVolumeModal.cpp \
        gui/modals/DBInfoModal.cpp \
    storage/Node.cpp \
    storage/StorageManifest.cpp \
    storage/StorageManifestVolume.cpp \
    storage/Volume.cpp \
        storage/dbsqlite/Appdb.cpp \
        core/models/VolumeModel.cpp \
        core/models/FileModel.cpp \
    storage/Storage.cpp \
    storage/models/DBInfoModel.cpp \
    lib/USettings.cpp \
    gui/ScanWorker.cpp \
    gui/facon/Facon.cpp


HEADERS += \
    gui/FilesListNavigator.hpp \
    gui/modals/EditVolumeModal.hpp \
    gui/FilesList.hpp \
        gui/MainWindow.hpp \
        gui/AddVolumeModal.hpp \
        gui/modals/DBInfoModal.hpp \
    gui/VolumesList.hpp \
    gui/modals/FaconModal.hpp \
    storage/Node.hpp \
    storage/StorageManifest.hpp \
    storage/StorageManifestVolume.hpp \
    storage/Volume.hpp \
        storage/dbsqlite/Appdb.hpp \
        storage/dbsqlite/models.hpp \
        core/models/VolumeModel.hpp \
        core/models/FileModel.hpp \
    storage/Storage.hpp \
    storage/models/DBInfoModel.hpp \
    gui/VolumeIcons.hpp \
    lib/USettings.hpp \
    gui/ScanWorker.hpp \
    gui/facon/Facon.hpp \
    lib/constants.hpp

FORMS += \
        gui/AddVolumeModal.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../appdb/release/ -lappdb
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../appdb/debug/ -lappdb
#else:unix:!macx: LIBS += -L$$OUT_PWD/../appdb/ -lappdb

#INCLUDEPATH += $$PWD/../appdb
#DEPENDPATH += $$PWD/../appdb

RESOURCES += \
    rc.qrc
