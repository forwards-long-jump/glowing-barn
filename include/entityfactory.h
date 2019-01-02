#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "magnetzippercomponent.h"
#include "playerinputcomponent.h"
#include "physicscomponent.h"
#include "magnetzipperreactorcomponent.h"
#include "hitboxcomponent.h"
#include "parallaxcomponent.h"
#include "debugcomponent.h"
#include "mapobject.h"
#include "imagecomponent.h"
#include "doorcomponent.h"
#include "gamebuttoncomponent.h"
#include "animationfactory.h"
#include "sparkcomponent.h"

/**
 * @brief The EntityFactory class.\nIt only contains static method to build entity
 */
class EntityFactory
{
public:
    static Entity* player(Tiled::MapObject*, Entity* = nullptr);
    static Entity* player(QPointF, QSizeF, Entity* = nullptr);

    static Entity *spark(Tiled::MapObject *object, Entity *parent);

    static Entity* collision(QPointF, QSizeF, Entity* = nullptr);

    static Entity* magnetZipper(Tiled::MapObject*, Entity * = nullptr);
    static Entity* magnetZipper(QPointF, QSizeF, QString, QSizeF, float, QString, Entity*);

    static Entity* graphic(Tiled::MapObject*, Entity* = nullptr);
    static Entity* door(Tiled::MapObject*, Entity * = nullptr);

    static MagnetZipperComponent::DIRECTION convertToDirection(const QString &);
    static Entity *gameButton(Tiled::MapObject *object, Entity *parent);

    static Input::Key convertToKey(const QString &str);

    // TODO: Get this dynamically from the map
    static const int TILE_SIZE = 16;
};

#endif // ENTITYFACTORY_H
