#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"

class GameScene : public Scene
{
    Q_OBJECT

public:
    GameScene(QString name = "default", Game *game = 0);
    ~GameScene();

};

#endif // GAMESCENE_H
