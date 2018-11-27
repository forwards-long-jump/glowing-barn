#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "entity.h"

class Game;

class Scene : public QGraphicsScene
{
public:
    Scene(QString name = "default", Game *game = 0);
    ~Scene();

protected:
    Game *game;
};

#include "game.h"

#endif // SCENE_H
