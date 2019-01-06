#include "scene.h"

Scene::Scene(QString name, Game* game)
    : QGraphicsScene()
{
    this->game = game;
    game->addScene(name, this);
    camera = new Camera();
}


void Scene::updateCamera()
{
    camera->update(this->views()[0]);
}


Scene::~Scene()
{
    delete camera;
}
