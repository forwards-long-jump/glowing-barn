#include "gamescene.h"
#include "entity.h"
#include "rectanglecomponent.h"
#include "playerinputcomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
}

GameScene::~GameScene()
{

}
