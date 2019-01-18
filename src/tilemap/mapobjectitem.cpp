#include "mapobjectitem.h"

/**
 * @brief MapObjectItem::MapObjectItem
 * @param mapObject
 * @param renderer
 * @param parent
 */
MapObjectItem::MapObjectItem(Tiled::MapObject* mapObject, Tiled::MapRenderer* renderer, QGraphicsItem* parent)
    : Entity(parent),
      mMapObject(mapObject),
      mRenderer(renderer)
{
    const QPointF &position = mapObject->position();
    const QPointF pixelPos = renderer->pixelToScreenCoords(position);

    QRectF boundingRect = renderer->boundingRect(mapObject);
    boundingRect.translate(-pixelPos);
    mBoundingRect = boundingRect;

    setPos(pixelPos);
    setRotation(mapObject->rotation());
}

/**
 * @brief MapObjectItem::boundingRect
 * @return
 */
QRectF MapObjectItem::boundingRect() const
{
    return mBoundingRect;
}

/**
 * @brief MapObjectItem::paint
 * @param painter
 * @param option
 * @param widget
 */
void MapObjectItem::paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Entity::paint(p, option, widget);

    const QColor &color = mMapObject->objectGroup()->color();
    p->translate(-pos());
    mRenderer->drawMapObject(p, mMapObject, color.isValid() ? color : Qt::darkGray);
}
