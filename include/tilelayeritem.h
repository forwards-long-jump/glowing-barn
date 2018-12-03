#ifndef TILELAYERITEM_H
#define TILELAYERITEM_H

#include "tilelayer.h"
#include "maprenderer.h"
#include "entity.h"

#include <QStyleOptionGraphicsItem>

/**
 * Item that represents a tile layer.
 */
class TileLayerItem : public Entity
{
public:
    TileLayerItem(Tiled::TileLayer *tileLayer, Tiled::MapRenderer *renderer, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *) override;

private:
    Tiled::TileLayer *mTileLayer;
    Tiled::MapRenderer *mRenderer;
};

#endif // TILELAYERITEM_H
