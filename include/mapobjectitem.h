#ifndef MAPOBJECTITEM_H
#define MAPOBJECTITEM_H

#include "mapobject.h"
#include "maprenderer.h"
#include "objectgroup.h"

#include <QGraphicsItem>

/**
 * Item that represents a map object.
 */
class MapObjectItem : public QGraphicsItem
{
public:
    MapObjectItem(Tiled::MapObject *mapObject, Tiled::MapRenderer *renderer, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    Tiled::MapObject *mMapObject;
    Tiled::MapRenderer *mRenderer;
    QRectF mBoundingRect;
};

#endif // MAPOBJECTITEM_H
