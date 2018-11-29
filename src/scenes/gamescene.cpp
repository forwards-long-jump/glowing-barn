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

    Entity* ref = new Entity(this);
    ref->addComponent(new RectangleComponent());
    ref->setX(ref->pos().x() + 60);
    ref->setY(ref->pos().y() + 60);
}

GameScene::~GameScene()
{

}
