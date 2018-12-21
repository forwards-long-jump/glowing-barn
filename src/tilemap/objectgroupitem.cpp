#include "objectgroupitem.h"

ObjectGroupItem::ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
ObjectGroupItem::ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, MapItem *parent)
    : Entity(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents);
    setPos(objectGroup->offset());

    const Tiled::ObjectGroup::DrawOrder drawOrder = objectGroup->drawOrder();

    // Create a child item for each object
    for (Tiled::MapObject *object : objectGroup->objects())
    {
        switch (object->cell().tileId()) {
        case 240:
            EntityFactory::magnetZipper(object, this);
            break;
        default:
            qWarning() << "unknown object";
            break;
        }
    }
}

QRectF ObjectGroupItem::boundingRect() const
{
    return QRectF();
}

void ObjectGroupItem::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Entity::paint(p, option, widget);
}
