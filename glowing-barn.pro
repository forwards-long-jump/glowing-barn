#-------------------------------------------------
#
# Project created by QtCreator 2018-10-10T10:39:15
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += multimedia
# TODO: REMOVE THIS AND DO NOT USE MUSICS AS RESOURCES
CONFIG += resources_big

CONFIG -= debug_and_release debug_and_release_target

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
!win32 {
    LIBS += -lz
}

include($$PWD/lib/libtiled/libtiled-static.pri)

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/main.cpp \
    src/game.cpp \
    src/entity.cpp \
    src/input.cpp \
    src/camera.cpp \
    src/sounds.cpp \
    src/animationfactory.cpp \
    src/particle.cpp \
    src/components/component.cpp \
    src/components/debug/debugtextcomponent.cpp \
    src/components/debug/debughitboxcomponent.cpp \
    src/components/debug/debugcomponent.cpp \
    src/components/gameplay/playerinputcomponent.cpp \
    src/components/gameplay/physicscomponent.cpp \
    src/components/gameplay/doorcomponent.cpp \
    src/components/gameplay/gamebuttoncomponent.cpp \
    src/components/gameplay/sparkcomponent.cpp \
    src/components/gameplay/hurtreactorcomponent.cpp \
    src/components/gameplay/soundbuttonreactorcomponent.cpp \
    src/components/graphics/graphicscomponent.cpp \
    src/components/graphics/parallaxcomponent.cpp \
    src/components/graphics/imagecomponent.cpp \
    src/components/graphics/animationcomponent.cpp \
    src/components/graphics/genericrendercomponent.cpp \
    src/components/graphics/transitioncomponent.cpp \
    src/components/graphics/particlespawnercomponent.cpp \
    src/components/hitboxes/squarehitboxcomponent.cpp \
    src/components/hitboxes/circlehitboxcomponent.cpp \
    src/components/hitboxes/hitboxreactorcomponent.cpp \
    src/components/hitboxes/interactivecomponent.cpp \
    src/components/hitboxes/interactivehitboxcomponent.cpp \
    src/components/hitboxes/hitboxcomponent.cpp \
    src/components/magnets/magnetzipperreactorcomponent.cpp \
    src/components/magnets/magnetzippercomponent.cpp \
    src/components/magnets/magnetjumpercomponent.cpp \
    src/components/magnets/magnetjumperreactorcomponent.cpp \
    src/components/magnets/magnetgravitycomponent.cpp \
    src/components/magnets/magnetgravityreactorcomponent.cpp \
    src/scenes/scene.cpp \
    src/scenes/gamescene.cpp \
    src/scenes/menuscene.cpp \
    src/scenes/creditsscene.cpp \
    src/state/playerstate.cpp \
    src/state/runningstate.cpp \
    src/state/standingstate.cpp \
    src/state/jumpingstate.cpp \
    src/state/skiddingstate.cpp \
    src/state/fallingstate.cpp \
    src/state/zippingstate.cpp \
    src/state/deadstate.cpp \
    src/tilemap/mapitem.cpp \
    src/tilemap/tilelayeritem.cpp \
    src/tilemap/objectgroupitem.cpp \
    src/tilemap/mapobjectitem.cpp \
    src/tilemap/entityfactory.cpp

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
    include/sparkcomponent.h \
    include/transitioncomponent.h \
    include/hurtreactorcomponent.h \
    include/magnetjumpercomponent.h \
    include/magnetjumperreactorcomponent.h \
    include/magnetgravitycomponent.h \
    include/magnetgravityreactorcomponent.h \
    include/genericrendercomponent.h \
    include/sounds.h \
    include/soundbuttonreactorcomponent.h \
    include/creditsscene.h \
    include/particle.h \
    include/particlespawnercomponent.h

RESOURCES += \
    assets/assets.qrc

!win32 {
    copydata.commands = $(COPY_DIR) $$PWD/assets $$OUT_PWD
}
win32 {
    copydata.commands = $(COPY_DIR) $$shell_path($$PWD/assets) $$shell_path($$OUT_PWD/assets)
}
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
