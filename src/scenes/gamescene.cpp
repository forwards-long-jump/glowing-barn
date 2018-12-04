#include "gamescene.h"
#include "entity.h"
#include "playerinputcomponent.h"
#include "debugcomponent.h"
#include "physicscomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
}

GameScene::~GameScene()
{

}
