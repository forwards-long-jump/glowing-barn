#include "objectgroupitem.h"

ObjectGroupItem::ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, MapItem *parent, QString spawnName)
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
        case 248:
            if(object->propertyAsString("spawnName") == spawnName) {
                static_cast<MapItem*>(parent)->setPlayer(EntityFactory::player(object, parent));
            }
            break;
        default:
            if(object->name() == "parallax-rect") {
                EntityFactory::parallaxRectangle(object, parent);
            }
            else if(object->name() == "door") {
                EntityFactory::door(object, parent);
            }
            else if(object->name() == "button") {
                EntityFactory::gameButton(object, parent);
            }
            else {
                qWarning() << "unknown object " << object->name();
            }
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
