#ifndef TILELAYERITEM_H
#define TILELAYERITEM_H

#include "tilelayer.h"
#include "maprenderer.h"
#include "entity.h"
#include "hitboxcomponent.h"

#include <QStyleOptionGraphicsItem>
#include <QVector>
#include <QRectF>

/**
 * Item that represents a tile layer.
 */
class TileLayerItem : public Entity
{
public:
    TileLayerItem(Tiled::TileLayer *tileLayer, Tiled::MapRenderer *renderer, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QVector<Entity *> createCollisions() const;

private:
    Tiled::TileLayer *mTileLayer;
    Tiled::MapRenderer *mRenderer;

    QRect findBoundsRect(int, int, int, QVector<bool>*) const;
};

#endif // TILELAYERITEM_H
