#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "input.h"
#include "entity.h"
#include "camera.h"

class Game;

/**
 * Contains the entities and the camera, also a QGraphicsScene
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class Scene : public QGraphicsScene
{
public:
    Scene(QString name = "default", Game* game = 0);
    ~Scene();

    virtual void onEnter() {}
    virtual void onLeave() {}
    virtual void onKeyChange(Input&) {}
    virtual void update() {}

    void updateCamera();

    Game* getGame() {return game;}
    Camera* getCamera() {return camera;}
protected:
    Game* game;
    Camera* camera;
};

#include "game.h"

#endif // SCENE_H
