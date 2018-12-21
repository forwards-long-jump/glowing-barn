#include "gamescene.h"
#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "magneticfieldreactorcomponent.h"

#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "hitboxcomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    loadMap(":maps/map-test.tmx");
}

GameScene::~GameScene()
{

}

bool GameScene::loadMap(QString filename)
{
    Tiled::MapReader reader;
    MapItem *mapItem;

    map = reader.readMap(filename);

    if (!map) {
        qWarning().noquote() << "Error:" << reader.errorString();
        return false;
    }

    mapRenderer = new Tiled::OrthogonalRenderer(map);
    mapItem = new MapItem(map, mapRenderer);
    mapItem->getLayer("middle")->createCollisions();

    camera->attachTo(mapItem->getPlayer());
    camera->setScaling(3);
    camera->setBoundingRect(QRectF(0, 0, map->width() * 16, 16 * map->height()));

    this->addItem(mapItem);

    return true;
}
