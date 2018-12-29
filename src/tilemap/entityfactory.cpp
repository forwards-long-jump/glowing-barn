#include "entityfactory.h"

Entity* EntityFactory::player(Tiled::MapObject* object, Entity* parent)
{
    return EntityFactory::player(object->position(), QSizeF(object->propertyAsString("w").toFloat(), object->propertyAsString("h").toFloat()), parent);
}

Entity* EntityFactory::player(QPointF pos, QSizeF size, Entity* parent)
{
    Entity* player = new Entity(parent, pos, size);
    QVector<QPair<QString, QVector<float>>> animations;
    AnimationComponent::addAnimationToVector("running", 8, 5, animations);
    AnimationComponent::addAnimationToVector("standing", 2, 15, animations);
    AnimationComponent::addAnimationToVector("skidding", 1, 1, animations);
    AnimationComponent::addAnimationToVector("jumping", 1, 1, animations);
    AnimationComponent::addAnimationToVector("zipping", 3, 10, animations);
    AnimationComponent* animationComponent = new AnimationComponent(":/entities/player.png", 16, animations);
    animationComponent->setCurrentAnimation("standing");

    player->addComponent(new PlayerInputComponent());
    player->addComponent(new PhysicsComponent());
    player->addComponent(new MagnetZipperReactorComponent());
    player->addComponent(animationComponent);

    return player;
}

Entity* EntityFactory::collision(QPointF pos, QSizeF size, Entity* parent)
{
    Entity *e = new Entity(parent, pos, size);
    e->addComponent(new SquareHitboxComponent("WallComponent"));

    return e;
}

Entity* EntityFactory::parallaxRectangle(Tiled::MapObject* object, Entity* parent)
{
    Entity *e = new Entity(parent, object->position(), object->size());
    e->addComponent(new ImageComponent(object->propertyAsString("texture")));
    e->addComponent(new ParallaxComponent(object->propertyAsString("parallax").toFloat()));
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
    pos.setY(pos.y() - 16);
    Entity *e = new Entity(parent, pos, size);
    e->addComponent(new MagnetZipperComponent(convertToDirection(direction), fieldSize, speed));
    e->addComponent(new DebugComponent(QColor("chartreuse"), true));

    return e;
}

MagnetZipperComponent::DIRECTION EntityFactory::convertToDirection(const QString& str)
{
    QString testStr(str.toUpper());

    if(testStr == "UP") return MagnetZipperComponent::DIRECTION::UP;
    else if(testStr == "DOWN") return MagnetZipperComponent::DIRECTION::DOWN;
    else if(testStr == "LEFT") return MagnetZipperComponent::DIRECTION::LEFT;
    else return MagnetZipperComponent::DIRECTION::RIGHT;
}
