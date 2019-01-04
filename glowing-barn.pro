#-------------------------------------------------
#
# Project created by QtCreator 2018-10-10T10:39:15
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = glowing-barn
TEMPLATE = app
RC_ICONS = assets/graphics/icon.ico

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
    src/camera.cpp \
    src/components/hitboxcomponent.cpp \
    src/components/debugtextcomponent.cpp \
    src/components/debughitboxcomponent.cpp \
    src/state/zippingstate.cpp \
    src/components/interactivecomponent.cpp \
    src/components/hitboxreactorcomponent.cpp \
    src/components/interactivehitboxcomponent.cpp \
    src/components/doorcomponent.cpp \
    src/tilemap/entityfactory.cpp \
    src/components/squarehitboxcomponent.cpp \
    src/components/circlehitboxcomponent.cpp \
    src/components/parallaxcomponent.cpp \
    src/components/imagecomponent.cpp \
    src/components/animationcomponent.cpp \
    src/components/magnetzipperreactorcomponent.cpp \
    src/components/magnetzippercomponent.cpp \
    src/components/gamebuttoncomponent.cpp \
    src/animationfactory.cpp \
    src/components/sparkcomponent.cpp

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
    include/physicscomponent.h \
    include/hitboxcomponent.h \
    include/debugtextcomponent.h \
    include/debughitboxcomponent.h \
    include/interactivecomponent.h \
    include/hitboxreactorcomponent.h \
    include/interactivehitboxcomponent.h \
    include/doorcomponent.h \
    include/entityfactory.h \
    include/squarehitboxcomponent.h \
    include/circlehitboxcomponent.h \
    include/parallaxcomponent.h \
    include/imagecomponent.h \
    include/animationcomponent.h \
    include/magnetzipperreactorcomponent.h \
    include/magnetzippercomponent.h \
    include/gamebuttoncomponent.h \
    include/animationfactory.h \
    include/sparkcomponent.h

RESOURCES += \
    assets/assets.qrc
