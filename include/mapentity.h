#ifndef MAPENTITY_H
#define MAPENTITY_H

#include "map.h"
#include "maprenderer.h"
#include "objectgroup.h"
#include "layer.h"
#include "entity.h"

#include <QMap>

class TileLayerEntity;

/**
 * Accesses, creates and contains TiledLayerItems
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class MapEntity : public Entity
{
public:
    MapEntity(Tiled::Map* map, Tiled::MapRenderer* renderer, QGraphicsItem* parent = nullptr, QString spawnName = "default");

    QRectF boundingRect() const override;
    void paint(QPainter* p, const QStyleOptionGraphicsItem* , QWidget* ) override;

    TileLayerEntity* getLayer(QString name) const;

    void setPlayer(Entity* _player) {this->player = _player;}
    Entity* getPlayer() const {return this->player;}

private:
    QMap<QString, TileLayerEntity*> layers;
    Entity* player = nullptr;
};

#include "objectlayerentity.h"
#include "tilelayerentity.h"

#endif // MAPENTITY_H
