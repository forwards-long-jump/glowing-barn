#include "gamescene.h"

#include "entity.h"
#include "rectanglecomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    Entity *e = new Entity(this, 50, 50);
    e->addComponent(new RectangleComponent());
}

GameScene::~GameScene()
{

}
