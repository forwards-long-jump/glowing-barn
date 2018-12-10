#include "gamescene.h"
#include "debugcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "magneticfieldreactorcomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    Entity *debugGround = new Entity(nullptr, 1000, 300);
    Entity *debugPlayer = new Entity(nullptr, 50, 50);
    Entity *debugMagnet = new Entity(nullptr, 30, 30);

    debugGround->setPos(-500, 1000);
    debugMagnet->setPos(100, 700);

    debugGround->addComponent(new DebugComponent("", "", Qt::black));
    debugMagnet->addComponent(new DebugComponent("", "", Qt::yellow));

    PlayerInputComponent *p = new PlayerInputComponent;
    debugPlayer->addComponent(new DebugComponent("", "", Qt::blue));
    debugPlayer->addComponent(p);
    p->init();
    debugPlayer->addComponent(new PhysicsComponent);
    debugPlayer->addComponent(new MagneticFieldReactorComponent);

    addItem(debugGround);
    addItem(debugPlayer);
    addItem(debugMagnet);

    camera->attachTo(debugPlayer);
    camera->setScaling(1);
}

GameScene::~GameScene()
{

}

bool GameScene::loadMap(QString filename)
{
    Tiled::MapReader reader;
    map = reader.readMap(filename);

    if (!map) {
        qWarning().noquote() << "Error:" << reader.errorString();
        return false;
    }

    mapRenderer = new Tiled::OrthogonalRenderer(map);

    for(Tiled::Layer *l : map->layers())
    {
        qInfo() << "Info:" << l->name();
    }

    this->addItem(new MapItem(map, mapRenderer));
}
