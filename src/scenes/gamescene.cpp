#include "gamescene.h"
#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"

#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "hitboxcomponent.h"
#include "animationcomponent.h"
#include "gamebuttoncomponent.h"

#include "doorcomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    changeMapScheduled = false;
    loadMap(":maps/map-test.tmx");

    // If a dev map is set, adds a file watcher to reload the map automatically every time it is changed on disk
    if(DEV_MAP_PATH != "") {
        mapReloadWatcher.addPath(DEV_MAP_PATH);
        connect(&mapReloadWatcher, &QFileSystemWatcher::fileChanged, this, [=] () {
            mapReloadWatcher.addPath(DEV_MAP_PATH);
            loadMap(DEV_MAP_PATH);
        });
    }
}

GameScene::~GameScene()
{

}

void GameScene::scheduleMapChange(QString mapPath, QString spawnName)
{
    changeMapScheduled = true;
    newMapPath = mapPath;
    newMapSpawn = spawnName;
}


void GameScene::update()
{
    if(changeMapScheduled)
    {
        changeMapScheduled = false;
        loadMap(newMapPath, newMapSpawn);
    }
}

void GameScene::onKeyChange(Input &input)
{

}

bool GameScene::loadMap(QString filename, QString spawnName)
{
    HitboxComponent::removeAll();
    clear();

    Tiled::MapReader reader;
    MapItem *mapItem;

    map = reader.readMap(filename);

    if (!map) {
        qWarning().noquote() << "Error:" << reader.errorString();
        return false;
    }

    mapRenderer = new Tiled::OrthogonalRenderer(map);
    mapItem = new MapItem(map, mapRenderer, nullptr, spawnName);
    mapItem->getLayer("middle")->createCollisions();

    mapItem->getLayer("front")->setZValue(1);
    mapItem->getPlayer()->setZValue(0);
    mapItem->getLayer("back")->setZValue(-1);

    camera->attachTo(mapItem->getPlayer());
    camera->setScaling(6);
    camera->setBoundingRect(QRectF(0, 0, map->width() * 16, 16 * map->height()));

    this->addItem(mapItem);

    return true;
}
