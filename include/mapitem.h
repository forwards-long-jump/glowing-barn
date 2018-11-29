#ifndef MAPITEM_H
#define MAPITEM_H

#include "map.h"
#include "tilelayer.h"
#include "maprenderer.h"
#include "tilelayeritem.h"
#include "objectgroup.h"
#include "objectgroupitem.h"

#include <QGraphicsItem>

class MapItem : public QGraphicsItem
{
public:
    MapItem(Tiled::Map *map, Tiled::MapRenderer *renderer, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
};

#endif // MAPITEM_H
