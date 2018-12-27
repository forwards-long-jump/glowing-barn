#include "gamescene.h"
#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "magneticfieldreactorcomponent.h"

#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "hitboxcomponent.h"
#include "imagecomponent.h"

#include "doorcomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    loadMap(":maps/map-test.tmx");

    Entity* door = new Entity(nullptr, 352, 48, 16, 32);
    addItem(door);
    door->addComponent(new DoorComponent());
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

    mapItem->getLayer("front")->setZValue(1);
    mapItem->getPlayer()->setZValue(0);
    mapItem->getLayer("back")->setZValue(-1);
    mapItem->getPlayer()->addComponent(new ImageComponent("/entities/player-static.png"));

    camera->attachTo(mapItem->getPlayer());
    camera->setScaling(3);
    camera->setBoundingRect(QRectF(0, 0, map->width() * 16, 16 * map->height()));

    this->addItem(mapItem);

    return true;
}
