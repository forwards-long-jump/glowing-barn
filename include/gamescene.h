#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "mapreader.h"
#include "map.h"
#include "orthogonalrenderer.h"
#include "mapitem.h"

#include <QDebug>
#include <QFileSystemWatcher>

class GameScene : public Scene
{
    Q_OBJECT
public:
    GameScene(QString name = "default", Game *game = 0);
    ~GameScene();

    void scheduleMapChange(QString mapPath, QString spawnName = "default");

private:
    // NOTE: Set this using absolute path to allow live map-reloading automatically when the file is changed on disk
    const QString DEV_MAP_PATH = "";

    void onKeyChange(Input &input) override;
    void update() override;

    bool loadMap(QString filename, QString spawnName = "default");

    // Tiled
    Tiled::Map *map;
    Tiled::MapRenderer *mapRenderer;

    bool changeMapScheduled;
    QString newMapPath;
    QString newMapSpawn;

    // Development related
    QFileSystemWatcher mapReloadWatcher;

};

#endif // GAMESCENE_H
