#include "gamescene.h"

#include "entity.h"
#include "playerinputcomponent.h"
#include "debugcomponent.h"
#include "physicscomponent.h"
#include "hitboxcomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    Entity* player = new Entity(nullptr, 10, 10);
    player->addComponent(new DebugComponent("", "", Qt::red));
    player->addComponent(new PlayerInputComponent());
    player->addComponent(new PhysicsComponent());
    player->addComponent(new HitboxComponent());
    addItem(player);

    Entity* bottomWall = new Entity(nullptr, 500, 50);
    bottomWall->addComponent(new DebugComponent("","", Qt::green));
    bottomWall->addComponent(new HitboxComponent("WallComponent"));
    bottomWall->setPos(-250, 50);
    addItem(bottomWall);

    Entity* rightWall = new Entity(nullptr, 50, 500);
    rightWall->addComponent(new DebugComponent("","", Qt::yellow));
    rightWall->addComponent(new HitboxComponent("WallComponent"));
    rightWall->setPos(250, -250);
    addItem(rightWall);

    Entity* leftWall = new Entity(nullptr, 50, 500);
    leftWall->addComponent(new DebugComponent("","",Qt::yellow));
    leftWall->addComponent(new HitboxComponent("WallComponent"));
    leftWall->setPos(-250, -250);
    addItem(leftWall);

    Entity* ceiling = new Entity(nullptr, 250, 50);
    ceiling->addComponent(new DebugComponent("","", Qt::green));
    ceiling->addComponent(new HitboxComponent("WallComponent"));
    ceiling->setPos(11, -40);
    addItem(ceiling);

    camera->attachTo(player);
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
