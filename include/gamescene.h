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
#include <QInputDialog>
#include <QDir>

class GameScene : public Scene
{
    Q_OBJECT
public:
    GameScene(QString name = "default", Game* game = 0);
    ~GameScene();

    void scheduleMapChange(QString mapPath = "", QString spawnName = "default");

    Entity* getPlayer() const;
private:
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
    QString devMapPath = "";
    bool canPressPauseKey = true;
    bool canPressMuteKey = true;
};

#endif // GAMESCENE_H
