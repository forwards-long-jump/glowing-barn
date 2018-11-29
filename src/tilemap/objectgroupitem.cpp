#include "include/objectgroupitem.h"

ObjectGroupItem::ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents);
    setPos(objectGroup->offset());

    const Tiled::ObjectGroup::DrawOrder drawOrder = objectGroup->drawOrder();

    // Create a child item for each object
    for (Tiled::MapObject *object : objectGroup->objects())
    {
        MapObjectItem *item = new MapObjectItem(object, renderer, this);
        if (drawOrder == Tiled::ObjectGroup::TopDownOrder)
        {
            item->setZValue(item->y());
        }
    }
}

QRectF ObjectGroupItem::boundingRect() const
{
    return QRectF();
}

void ObjectGroupItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}
