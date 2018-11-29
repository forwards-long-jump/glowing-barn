#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "mapreader.h"
#include "map.h"
#include "orthogonalrenderer.h"
#include "mapitem.h"

#include <QDebug>

class GameScene : public Scene
{
    Q_OBJECT

public:
    GameScene(QString name = "default", Game *game = 0);
    ~GameScene();

private:
    bool loadMap(QString filename);

    // Tiled
    Tiled::Map *map;
    Tiled::MapRenderer *mapRenderer;

};

#endif // GAMESCENE_H
