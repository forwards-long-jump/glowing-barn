#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "mapreader.h"
#include "map.h"
#include "orthogonalrenderer.h"
#include "mapentity.h"

#include <QFileSystemWatcher>
#include <QInputDialog>
#include <QDir>

/**
 * Scene which features a playable character
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

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
    MapEntity* mapItem;
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

#include "hitboxcomponent.h"
#include "transitioncomponent.h"
#include "sounds.h"
#include "genericrendercomponent.h"
#include "guiitemcomponent.h"

#include <QDebug>

#endif // GAMESCENE_H
