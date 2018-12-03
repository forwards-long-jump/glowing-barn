#ifndef OBJECTGROUPITEM_H
#define OBJECTGROUPITEM_H

#include "objectgroup.h"
#include "maprenderer.h"
#include "mapobject.h"
#include "mapobjectitem.h"
#include "entity.h"

/**
 * Item that represents an object group.
 */
class ObjectGroupItem : public Entity
{
public:
    ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *) override;
};

#endif // OBJECTGROUPITEM_H
