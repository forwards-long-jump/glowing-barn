#include "entityfactory.h"

Entity* EntityFactory::player(Tiled::MapObject* object, Entity* parent)
{
    return EntityFactory::player(object->position(), QSizeF(object->propertyAsString("w").toFloat(), object->propertyAsString("h").toFloat()), parent);
}

Entity* EntityFactory::player(QPointF pos, QSizeF size, Entity* parent)
{
    Entity* player = new Entity(parent, size);
    player->setPos(pos);
    player->addComponent(new DebugComponent(Qt::red));
    player->addComponent(new PlayerInputComponent());
    player->addComponent(new PhysicsComponent());
    player->addComponent(new MagneticFieldReactorComponent());

    return player;
}

Entity* EntityFactory::collision(QPointF pos, QSizeF size, Entity* parent)
{
    Entity *e = new Entity(parent, size);
    e->setPos(pos);
    e->addComponent(new HitboxComponent("WallComponent"));

    return e;
}

Entity* EntityFactory::magnetZipper(Tiled::MapObject* object, Entity* parent)
{
    return EntityFactory::magnetZipper(object->position(), object->size(), object->propertyAsString("direction"),
                                            QSizeF(object->propertyAsString("w").toFloat(), object->propertyAsString("h").toFloat()),
                                            object->propertyAsString("speed").toFloat(), parent);
}

Entity* EntityFactory::magnetZipper(QPointF pos, QSizeF size, QString direction, QSizeF fieldSize, float speed, Entity* parent)
{
    Entity *e = new Entity(parent, size);
    e->setPos(pos.x(), pos.y() - 16);
    e->addComponent(new ZipperMagnetComponent(convertToDirection(direction), fieldSize, speed));
    e->addComponent(new DebugComponent(QColor("chartreuse"), true));

    return e;
}

ZipperMagnetComponent::DIRECTION EntityFactory::convertToDirection(const QString& str)
{
    QString testStr(str.toUpper());

    if(testStr == "UP") return ZipperMagnetComponent::DIRECTION::UP;
    else if(testStr == "DOWN") return ZipperMagnetComponent::DIRECTION::DOWN;
    else if(testStr == "LEFT") return ZipperMagnetComponent::DIRECTION::LEFT;
    else return ZipperMagnetComponent::DIRECTION::RIGHT;
}
