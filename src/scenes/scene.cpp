#include "scene.h"

Scene::Scene(QString name, Game *game)
    : QGraphicsScene()
{
    this->game = game;
    game->addScene(name, this);
}
