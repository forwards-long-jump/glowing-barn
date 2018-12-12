#include "gamescene.h"
#include "entity.h"
#include "playerinputcomponent.h"

GameScene::GameScene(QString name, Game *game)
    : Scene(name, game)
{
    loadMap(":maps/map-test.tmx");
}

GameScene::~GameScene()
{

}

bool GameScene::loadMap(QString filename)
{
    Tiled::MapReader reader;
    MapItem *mapItem;

    map = reader.readMap(filename);

    if (!map) {
        qWarning().noquote() << "Error:" << reader.errorString();
        return false;
    }

    mapRenderer = new Tiled::OrthogonalRenderer(map);

    for(Tiled::Layer *l : map->layers())
    {
        qInfo() << "Info:" << l->name();
    }

    mapItem = new MapItem(map, mapRenderer);
    this->addItem(mapItem);

    return true;
}
