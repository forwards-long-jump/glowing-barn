#include "include/mapitem.h"

MapItem::MapItem(Tiled::Map *map, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : Entity(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents);

    // Create a child item for each layer
    for (Tiled::Layer *layer : map->layers()) {
        if (Tiled::TileLayer *tileLayer = layer->asTileLayer())
        {
            layers.insert(layer->name(), new TileLayerItem(tileLayer, renderer, this));
        }
        else if (Tiled::ObjectGroup *objectGroup = layer->asObjectGroup())
        {
            new ObjectGroupItem(objectGroup, renderer, this);
        }
    }
}

QRectF MapItem::boundingRect() const
{
    return QRectF();
}

void MapItem::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Entity::paint(p, option, widget);
}

TileLayerItem* MapItem::getLayer(QString name) const
{
    return layers.value(name);
}
