#-------------------------------------------------
#
# Project created by QtCreator 2018-10-10T10:39:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = glowing-barn
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

!win {
    LIBS += -lz
}

include($$PWD/lib/libtiled/libtiled-static.pri)

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/main.cpp \
    src/game.cpp \
    src/entity.cpp \
    src/input.cpp \
    src/scenes/gamescene.cpp \
    src/scenes/menuscene.cpp \
    src/scenes/scene.cpp \
    src/components/component.cpp \
    src/components/graphicscomponent.cpp \
    src/components/playerinputcomponent.cpp \
    src/components/debugcomponent.cpp \
    src/components/physicscomponent.cpp \
    src/tilemap/mapitem.cpp \
    src/tilemap/tilelayeritem.cpp \
    src/tilemap/objectgroupitem.cpp \
    src/tilemap/mapobjectitem.cpp \
    src/state/playerstate.cpp \
    src/state/runningstate.cpp \
    src/state/standingstate.cpp \
    src/state/jumpingstate.cpp \
    src/state/skiddingstate.cpp \
    src/state/fallingstate.cpp \
    src/camera.cpp

HEADERS += \
    include/game.h \
    include/entity.h \
    include/gamescene.h \
    include/menuscene.h \
    include/scene.h \
    include/component.h \
    include/graphicscomponent.h \
    include/mapitem.h \
    include/tilelayeritem.h \
    include/objectgroupitem.h \
    include/mapobjectitem.h \
    include/input.h \
    include/playerinputcomponent.h \
    include/playerstate.h \
    include/debugcomponent.h \
    include/camera.h \
    include/physicscomponent.h


RESOURCES += \
    assets/assets.qrc
