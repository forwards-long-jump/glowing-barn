#include "include/mapobjectitem.h"

MapObjectItem::MapObjectItem(Tiled::MapObject *mapObject, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : Entity(parent)
    , mMapObject(mapObject)
    , mRenderer(renderer)
{
    const QPointF &position = mapObject->position();
    const QPointF pixelPos = renderer->pixelToScreenCoords(position);

    QRectF boundingRect = renderer->boundingRect(mapObject);
    boundingRect.translate(-pixelPos);
    mBoundingRect = boundingRect;

    setPos(pixelPos);
    setRotation(mapObject->rotation());
}

QRectF MapObjectItem::boundingRect() const
{
    return mBoundingRect;
}

void MapObjectItem::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Entity::paint(p, option, widget);

    const QColor &color = mMapObject->objectGroup()->color();
    p->translate(-pos());
    mRenderer->drawMapObject(p, mMapObject, color.isValid() ? color : Qt::darkGray);
}
