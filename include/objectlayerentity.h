#ifndef OBJECTLAYERENTITY_H
#define OBJECTLAYERENTITY_H

#include "maprenderer.h"
#include "objectgroup.h"
#include "entity.h"

#include <QDebug>

/**
 * Represents an object's layer in Tiled and call the EntityFactory to create the level
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class ObjectLayerEntity : public Entity
{
public:
    ObjectLayerEntity(Tiled::ObjectGroup* objectGroup, Tiled::MapRenderer* renderer, Entity* parent, QString spawnName);

    QRectF boundingRect() const override;
    void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* ) override;
};

#include "entityfactory.h"

#endif // OBJECTLAYERENTITY_H
