#include "include/tilelayeritem.h"

TileLayerItem::TileLayerItem(Tiled::TileLayer *tileLayer, Tiled::MapRenderer *renderer, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , mTileLayer(tileLayer)
    , mRenderer(renderer)
{
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption);
    setPos(mTileLayer->offset());
}

QRectF TileLayerItem::boundingRect() const
{
    return mRenderer->boundingRect(mTileLayer->bounds());
}

void TileLayerItem::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *)
{
    mRenderer->drawTileLayer(p, mTileLayer, option->rect);
}
