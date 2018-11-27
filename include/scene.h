#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Game;

class Scene : public QGraphicsScene
{
public:
    Scene(QString name = "default", Game *game = 0);
    ~Scene();

    Game* getGame() {return game;}
protected:
    Game *game;
};

#include "game.h"

#endif // SCENE_H
