#include "scene.h"

/**
 * @brief Scene::Scene
 * @param name
 * @param game
 */
Scene::Scene(QString name, Game* game)
    : QGraphicsScene()
{
    this->game = game;
    game->addScene(name, this);
    camera = new Camera();
}

/**
 * @brief Scene::updateCamera
 */
void Scene::updateCamera()
{
    camera->update(this->views()[0]);
}

/**
 * @brief Scene::~Scene
 */
Scene::~Scene()
{
    delete camera;
}
