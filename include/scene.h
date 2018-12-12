#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "entity.h"
#include "camera.h"

class Game;

class Scene : public QGraphicsScene
{
public:
    Scene(QString name = "default", Game *game = 0);
    ~Scene();

    void updateCamera();
    Game* getGame() {return game;}
protected:
    Game *game;
    Camera *camera;
};

#include "game.h"

#endif // SCENE_H
