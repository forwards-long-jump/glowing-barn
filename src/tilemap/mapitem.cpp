#include "include/mapitem.h"

MapItem::MapItem(Tiled::Map *map, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents);

    // Create a child item for each layer
    for (Tiled::Layer *layer : map->layers()) {
        if (Tiled::TileLayer *tileLayer = layer->asTileLayer())
        {
            new TileLayerItem(tileLayer, renderer, this);
        }
        /*else if (Tiled::ObjectGroup *objectGroup = layer->asObjectGroup())
        {
            new ObjectGroupItem(objectGroup, renderer, this);
        }*/
    }
}

QRectF MapItem::boundingRect() const
{
    return QRectF();
}

void MapItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}
