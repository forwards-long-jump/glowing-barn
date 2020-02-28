#include "mapentity.h"

/**
 * @brief MapEntity::MapEntity
 * @param map
 * @param renderer
 * @param parent
 * @param spawnName
 */
MapEntity::MapEntity(Tiled::Map* map, Tiled::MapRenderer* renderer, QGraphicsItem* parent, QString spawnName, Game *game)
    : Entity(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents);

    // Create a child item for each layer
    for (Tiled::Layer* layer : map->layers()) {
        if (Tiled::TileLayer* tileLayer = layer->asTileLayer())
        {
            layers.insert(layer->name(), new TileLayerEntity(tileLayer, renderer, this));
        }
        else if (Tiled::ObjectGroup* objectGroup = layer->asObjectGroup())
        {
            new ObjectLayerEntity(objectGroup, renderer, this, spawnName, game);
        }
    }
}

/**
 * @brief MapEntity::boundingRect
 * @return
 */
QRectF MapEntity::boundingRect() const
{
    return QRectF();
}

/**
 * @brief MapEntity::paint
 * @param p
 * @param option
 * @param widget
 */
void MapEntity::paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Entity::paint(p, option, widget);
}

/**
 * @brief MapEntity::getLayer
 * @param name
 * @return
 */
TileLayerEntity* MapEntity::getLayer(QString name) const
{
    return layers.value(name);
}
