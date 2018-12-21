#ifndef TILELAYERITEM_H
#define TILELAYERITEM_H

#include "tilelayer.h"
#include "maprenderer.h"
#include "entity.h"
#include "hitboxcomponent.h"
#include "entityfactory.h"
#include "mapitem.h"

#include <QStyleOptionGraphicsItem>
#include <QVector>
#include <QRectF>

/**
 * Item that represents a tile layer.
 */
class TileLayerItem : public Entity
{
public:
    TileLayerItem(Tiled::TileLayer *tileLayer, Tiled::MapRenderer *renderer, MapItem *parent);

    QRectF boundingRect() const override;

    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void createCollisions();

private:
    Tiled::TileLayer *mTileLayer;
    Tiled::MapRenderer *mRenderer;
    QVector<Entity*> collisions;

    QRect findBoundsRect(int, int, int, QVector<bool>*) const;
};

#endif // TILELAYERITEM_H
