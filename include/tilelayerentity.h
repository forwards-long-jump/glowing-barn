#ifndef TILELAYERENTITY_H
#define TILELAYERENTITY_H

#include "maprenderer.h"
#include "tilelayer.h"
#include "entity.h"

#include <QStyleOptionGraphicsItem>
#include <QVector>
#include <QRectF>

/**
 * Represents a tile layer, and creates collision hitboxes
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class TileLayerEntity : public Entity
{
public:
    TileLayerEntity(Tiled::TileLayer* tileLayer, Tiled::MapRenderer* renderer, Entity* parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void createCollisions();

private:
    Tiled::TileLayer* tileLayer;
    Tiled::MapRenderer* renderer;

    QRect findBoundsRect(int, int, int, QVector<bool>*) const;
};

#include "entityfactory.h"

#endif // TILELAYERENTITY_H
