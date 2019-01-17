#ifndef OBJECTGROUPITEM_H
#define OBJECTGROUPITEM_H

#include "objectgroup.h"
#include "maprenderer.h"
#include "mapobject.h"
#include "mapobjectitem.h"
#include "entityfactory.h"
#include "entity.h"
#include "mapitem.h"

#include <QDebug>

/**
 * lel
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class ObjectGroupItem : public Entity
{
public:
    ObjectGroupItem(Tiled::ObjectGroup* objectGroup, Tiled::MapRenderer* renderer, MapItem* parent, QString spawnName);

    MagnetZipperComponent::DIRECTION convertToDirection(const QString& str);

    QRectF boundingRect() const override;
    void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* ) override;
};

#endif // OBJECTGROUPITEM_H
