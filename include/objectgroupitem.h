#ifndef OBJECTGROUPITEM_H
#define OBJECTGROUPITEM_H

#include "objectgroup.h"
#include "maprenderer.h"
#include "mapobject.h"
#include "mapobjectitem.h"

#include <QGraphicsItem>

/**
 * Item that represents an object group.
 */
class ObjectGroupItem : public QGraphicsItem
{
public:
    ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
};

#endif // OBJECTGROUPITEM_H
