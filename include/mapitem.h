#ifndef MAPITEM_H
#define MAPITEM_H

#include "map.h"
#include "tilelayer.h"
#include "maprenderer.h"
#include "objectgroup.h"
#include "entity.h"

#include <QMap>

class TileLayerItem;
class ObjectGroupItem;

/**
 * Accesses, creates and contains TiledLayerItems
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class MapItem : public Entity
{
public:
    MapItem(Tiled::Map* map, Tiled::MapRenderer* renderer, QGraphicsItem* parent = nullptr, QString spawnName = "default");

    QRectF boundingRect() const override;
    void paint(QPainter* p, const QStyleOptionGraphicsItem* , QWidget* ) override;

    TileLayerItem* getLayer(QString name) const;

    void setPlayer(Entity* _player) {this->player = _player;}
    Entity* getPlayer() const {return this->player;}

private:
    QMap<QString, TileLayerItem*> layers;
    Entity* player = nullptr;
};

#include "objectgroupitem.h"
#include "tilelayeritem.h"

#endif // MAPITEM_H
