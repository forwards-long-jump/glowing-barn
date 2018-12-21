#ifndef MAPITEM_H
#define MAPITEM_H

#include "map.h"
#include "tilelayer.h"
#include "maprenderer.h"
#include "tilelayeritem.h"
#include "objectgroup.h"
#include "objectgroupitem.h"
#include "entity.h"

#include <QMap>

class TileLayerItem;
class ObjectGroupItem;

class MapItem : public Entity
{
public:
    MapItem(Tiled::Map *map, Tiled::MapRenderer *renderer, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;

    TileLayerItem* getLayer(QString name) const;

private:
    QMap<QString, TileLayerItem *> layers;
};

#include "objectgroupitem.h"
#include "tilelayeritem.h"

#endif // MAPITEM_H
