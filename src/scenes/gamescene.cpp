#include "gamescene.h"
#include "entity.h"
#include "rectanglecomponent.h"
#include "playerinputcomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    Entity* test = new Entity(this);
    test->addComponent(new RectangleComponent());
    test->addComponent(new PlayerInputComponent());
}

GameScene::~GameScene()
{

}
