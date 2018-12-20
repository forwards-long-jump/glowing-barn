#include "objectgroupitem.h"

ObjectGroupItem::ObjectGroupItem(Tiled::ObjectGroup *objectGroup, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : Entity(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents);
    setPos(objectGroup->offset());

    const Tiled::ObjectGroup::DrawOrder drawOrder = objectGroup->drawOrder();

    // Create a child item for each object
    for (Tiled::MapObject *object : objectGroup->objects())
    {
        switch (object->cell().tileId()) {
        case 240: {
            Entity *e = new Entity(this, object->width(), object->height());
            e->setPos(object->x(), object->y() - 16);
            e->addComponent(new ZipperMagnetComponent(convertToDirection(object->propertyAsString("direction")), QSizeF(object->propertyAsString("w").toFloat(),
                                                            (int)object->propertyAsString("h").toFloat()), object->propertyAsString("speed").toFloat()));

            e->addComponent(new DebugComponent(QColor("chartreuse"), true)); // TODO : Add graphics
        }
            break;
        default:
            qWarning() << "unknown object";
            break;
        }
    }
}

ZipperMagnetComponent::DIRECTION ObjectGroupItem::convertToDirection(const QString& str)
{
    QString testStr(str.toUpper());

    if(testStr == "UP") return ZipperMagnetComponent::DIRECTION::UP;
    else if(testStr == "DOWN") return ZipperMagnetComponent::DIRECTION::DOWN;
    else if(testStr == "LEFT") return ZipperMagnetComponent::DIRECTION::LEFT;
    else if(testStr == "RIGHT") return ZipperMagnetComponent::DIRECTION::RIGHT;
}

QRectF ObjectGroupItem::boundingRect() const
{
    return QRectF();
}

void ObjectGroupItem::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Entity::paint(p, option, widget);
}
