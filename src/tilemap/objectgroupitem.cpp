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
        case 235:
            EntityFactory::box(object, this);
            break;
        case 236:
            // TODO: Grappling magnet
            break;
        case 237:
            EntityFactory::magnetJumper(object, this);
            break;
        case 238:
            EntityFactory::magnetGravity(object, this);
            break;
        default:
            if(object->name() == "graphic") {
                EntityFactory::graphic(object, parent);
            }
            else if(object->name() == "door") {
                EntityFactory::door(object, parent);
            }
            else if(object->name() == "button") {
                EntityFactory::gameButton(object, parent);
            }
            else if(object->name() == "spark") {
                EntityFactory::spark(object, parent);
            }
            else if(object->name() == "hurt") {
                EntityFactory::hurt(object, parent);
            }
            else if(object->name() == "sound") {
                EntityFactory::soundButtonReactor(object, parent);
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
