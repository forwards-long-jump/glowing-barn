#ifndef MAPOBJECTITEM_H
#define MAPOBJECTITEM_H

#include "mapobject.h"
#include "maprenderer.h"
#include "objectgroup.h"
#include "entity.h"

/**
 * Item that represents a map object.
 */
class MapObjectItem : public Entity
{
public:
    MapObjectItem(Tiled::MapObject *mapObject, Tiled::MapRenderer *renderer, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Tiled::MapObject *mMapObject;
    Tiled::MapRenderer *mRenderer;
    QRectF mBoundingRect;
};

#endif // MAPOBJECTITEM_H
