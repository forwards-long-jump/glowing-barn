#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "input.h"
#include "entity.h"
#include "camera.h"

class Game;

class Scene : public QGraphicsScene
{
public:
    Scene(QString name = "default", Game* game = 0);
    ~Scene();

    void updateCamera();
    virtual void onKeyChange(Input &input) {}
    virtual void update() {}

    Game* getGame() {return game;}
    Camera* getCamera() {return camera;}
protected:
    Game* game;
    Camera* camera;
};

#include "game.h"

#endif // SCENE_H
