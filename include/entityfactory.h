#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "zippermagnetcomponent.h"
#include "hitboxcomponent.h"
#include "debugcomponent.h"
#include "mapobject.h"

/**
 * @brief The EntityFactory class.\nIt only contains static method to build entity
 */
class EntityFactory
{
public:
    static Entity* player(Tiled::MapObject*, Entity* = nullptr){}
    static Entity* player(QPointF, QSizeF){}

    static Entity* collision(QPointF, QSizeF, Entity* = nullptr);

    static Entity* magnetZipper(Tiled::MapObject*, Entity* = nullptr);
    static Entity* magnetZipper(QPointF, QSizeF, QString, QSizeF, float, Entity* = nullptr);

    static ZipperMagnetComponent::DIRECTION convertToDirection(const QString &);
};

#endif // ENTITYFACTORY_H
