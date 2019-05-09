QT += quick sql
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audioplayer.cpp \
    itemtrack.cpp \
        main.cpp \
    tagsource.cpp \
    tortoise.cpp \
    dbase.cpp \
    dbasemanager.cpp \
    dbasecontroller.cpp \
    viewermodel.cpp \
    itemartist.cpp \
    viewerartistsmodel.cpp \
    playlistmodel.cpp

RESOURCES += qml.qrc \
    icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    audioplayer.h \
    itemtrack.h \
    tagsource.h \
    tortoise.h \
    dbase.h \
    dbasemanager.h \
    dbasecontroller.h \
    viewermodel.h \
    itemartist.h \
    viewerartistsmodel.h \
    playlistmodel.h

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -ltag

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libtag.a

DISTFILES += \
    PlaylistPanel.qml \
    TrackDelegateAlbums.qml \
    ViewPage.qml
