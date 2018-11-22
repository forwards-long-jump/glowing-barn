#include "gamescene.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    this->game = game;
}

GameScene::~GameScene()
{

}
