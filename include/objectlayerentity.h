#ifndef OBJECTLAYERENTITY_H
#define OBJECTLAYERENTITY_H

#include "maprenderer.h"
#include "objectgroup.h"
#include "entity.h"
//#include "magnetzippercomponent.h"

#include <QDebug>

/**
 * lel
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class ObjectLayerEntity : public Entity
{
public:
    ObjectLayerEntity(Tiled::ObjectGroup* objectGroup, Tiled::MapRenderer* renderer, Entity* parent, QString spawnName);

    //MagnetZipperComponent::DIRECTION convertToDirection(const QString& str);

    QRectF boundingRect() const override;
    void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* ) override;
};

#include "entityfactory.h"

#endif // OBJECTLAYERENTITY_H
