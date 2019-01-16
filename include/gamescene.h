#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "mapreader.h"
#include "map.h"
#include "orthogonalrenderer.h"
#include "mapitem.h"

#include "hitboxcomponent.h"
#include "transitioncomponent.h"
#include "sounds.h"
#include "genericrendercomponent.h"
#include "guiitemcomponent.h"

#include <QDebug>
#include <QFileSystemWatcher>

class GameScene : public Scene
{
    Q_OBJECT
public:
    GameScene(QString name = "default", Game* game = 0);
    ~GameScene();

    void scheduleMapChange(QString mapPath = "", QString spawnName = "default");

    Entity* getPlayer() const;
private:
    // NOTE: Set this using absolute path to allow live map-reloading automatically when the file is changed on disk
    const QString DEV_MAP_PATH = "";

    void onEnter() override;
    void onKeyChange(Input&) override;
    void update() override;

    bool loadMap(QString filename, QString spawnName = "default");

    // Tiled
    Tiled::Map* map;
    MapItem* mapItem;
    Tiled::MapRenderer* mapRenderer;

    bool changeMapScheduled = false;
    QString newMapPath = "";
    QString newMapSpawn = "";

    // Development related
    QFileSystemWatcher mapReloadWatcher;
    bool canPressPauseKey = true;
    bool canPressMuteKey = true;
};

#endif // GAMESCENE_H
