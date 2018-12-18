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
    Entity* player = new Entity(nullptr, 8, 16);
    player->setPos(32, 32);
    player->addComponent(new DebugComponent(Qt::red));
    player->addComponent(new PlayerInputComponent());
    player->addComponent(new PhysicsComponent());
    player->addComponent(new MagneticFieldReactorComponent());
    addItem(player);

    loadMap(":maps/map-test.tmx");

    camera->attachTo(player);
    //camera->setScaling(5);
    camera->setBoundingRect(QRectF(0, 0, map->width() * 16, 16 * map->height()));
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

    this->addItem(mapItem);

    for(auto elem : mapItem->getLayer("middle")->createCollisions())
    {
        this->addItem(elem);
    }

    return true;
}
