#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "zippermagnetcomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "magneticfieldreactorcomponent.h"
#include "hitboxcomponent.h"
#include "parallaxcomponent.h"
#include "debugcomponent.h"
#include "mapobject.h"
#include "imagecomponent.h"

/**
 * @brief The EntityFactory class.\nIt only contains static method to build entity
 */
class EntityFactory
{
public:
    static Entity* player(Tiled::MapObject*, Entity* = nullptr);
    static Entity* player(QPointF, QSizeF, Entity* = nullptr);

    static Entity* collision(QPointF, QSizeF, Entity* = nullptr);

    static Entity* magnetZipper(Tiled::MapObject*, Entity* = nullptr);
    static Entity* magnetZipper(QPointF, QSizeF, QString, QSizeF, float, Entity* = nullptr);

    static Entity* parallaxRectangle(Tiled::MapObject*, Entity* = nullptr);

    static ZipperMagnetComponent::DIRECTION convertToDirection(const QString &);
};

#endif // ENTITYFACTORY_H
