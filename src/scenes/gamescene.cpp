#include "gamescene.h"

#include "entity.h"
#include "rectanglecomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
}

GameScene::~GameScene()
{

}
