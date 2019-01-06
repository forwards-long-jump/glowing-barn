#include "entityfactory.h"

Entity* EntityFactory::player(Tiled::MapObject* object, Entity* parent)
{
    return EntityFactory::player(object->position(), QSizeF(object->propertyAsString("w").toFloat(), object->propertyAsString("h").toFloat()), object->propertyAsString("animationName"), parent);
}

Entity* EntityFactory::player(QPointF pos, QSizeF size, QString animationName, Entity* parent)
{
    Entity* player = new Entity(parent, pos, size);

    AnimationComponent* animationComponent = AnimationFactory::getAnimationComponent(animationName);
    animationComponent->setCurrentAnimation("standing");

    // Attracts items with a BoxGravityHitbox reactor
    player->addComponent(new MagnetGravityComponent(100, -0.7, "", QPointF(size.width() / 2, -5), "BoxGravityHitbox", "PlayerGravityMagnet"));
    player->addComponent(new SquareHitboxComponent(GameButtonComponent::HITBOX_REACTOR_NAME));
    player->addComponent(new SquareHitboxComponent(SparkComponent::HITBOX_REACTOR_NAME));
    player->addComponent(new PlayerInputComponent());
    player->addComponent(new PhysicsComponent());
    player->addComponent(new HurtReactorComponent());
    player->addComponent(new MagnetZipperReactorComponent());
    player->addComponent(new MagnetJumperReactorComponent());
    player->addComponent(new MagnetGravityReactorComponent());
    player->addComponent(animationComponent);

    return player;
}

Entity* EntityFactory::hurt(Tiled::MapObject* object, Entity* parent)
{
    Entity* e = new Entity(parent, object->position(), object->size());
    e->addComponent(new SquareHitboxComponent(HurtReactorComponent::HITBOX_REACTOR_NAME));
    return e;
}

Entity* EntityFactory::spark(Tiled::MapObject* object, Entity* parent)
{
    Entity* spark = new Entity(parent, object->position(), object->size());
    AnimationComponent* animationComponent = AnimationFactory::getAnimationComponent("spark");
    animationComponent->setCurrentAnimation("idle");
    spark->addComponent(animationComponent);
    spark->addComponent(new SparkComponent(object->property("radius").toFloat(), object->propertyAsString("hitboxName")));
    CircleHitboxComponent* chc = new CircleHitboxComponent(HurtReactorComponent::HITBOX_REACTOR_NAME);
    chc->setRadius(object->size().width() * 0.8);
    spark->addComponent(chc);

    return spark;
}

Entity* EntityFactory::collision(QPointF pos, QSizeF size, Entity* parent)
{
    Entity *e = new Entity(parent, pos, size);
    e->addComponent(new SquareHitboxComponent("WallComponent"));
    return e;
}

Entity* EntityFactory::gameButton(Tiled::MapObject* object, Entity* parent)
{
    Entity *e = new Entity(parent, object->position(), object->size());

    if(object->propertyAsString("requiredKey") != "")
    {
        e->addComponent(new GameButtonComponent(
                            object->propertyAsString("name"),
                            convertToKey(object->propertyAsString("requiredKey")),
                            object->property("stayPressed").toBool(),
                            object->property("invertOnOff").toBool(),
                            object->propertyAsString("pressedDurationInTick").toInt(),
                            object->property("isTogglable").toBool(),
                            object->propertyAsString("requiredButtonsToPress"),
                            object->propertyAsString("requiredButtonsToRelease")
                        ));
    }
    else
    {
         e->addComponent(new GameButtonComponent(
                             object->propertyAsString("name"),
                             object->property("stayPressed").toBool(),
                             object->property("invertOnOff").toBool(),
                             object->propertyAsString("pressedDurationInTick").toInt(),
                             object->property("isTogglable").toBool(),
                             object->propertyAsString("requiredButtonsToPress"),
                             object->propertyAsString("requiredButtonsToRelease"),
                             object->propertyAsString("pressableBy") == "" ? GameButtonComponent::HITBOX_REACTOR_NAME : object->propertyAsString("pressableBy")
                         ));
    }

    return e;
}

Entity* EntityFactory::door(Tiled::MapObject* object, Entity* parent)
{
    // Door and button
    Entity *e = new Entity(parent, object->position(), object->size());
    e->addComponent(new DoorComponent(object->propertyAsString("targetMap"), object->propertyAsString("targetSpawn")));
    e->addComponent(new GameButtonComponent("auto_door",Input::Key::INTERACT, false, false, 1, true));

    // The door animation has a bigger size, so we create a new component for it
    Entity *a = new Entity(parent, object->position() - QPointF(0, 16), QSizeF(16, 64));
    AnimationComponent* ac = AnimationFactory::getAnimationComponent("door");
    ac->setCurrentAnimation("idle");
    ac->setButtons("auto_door");
    a->addComponent(ac);
    a->addComponent(new ParallaxComponent(0.0001));
    return e;
}

Entity* EntityFactory::magnetZipper(Tiled::MapObject* object, Entity* parent)
{
    return EntityFactory::magnetZipper(object->position(), object->size(), object->propertyAsString("direction"),
                                            QSizeF(object->propertyAsString("w").toFloat(), object->propertyAsString("h").toFloat()),
                                            object->propertyAsString("speed").toFloat(), object->propertyAsString("buttons"), parent);
}

Entity* EntityFactory::magnetZipper(QPointF pos, QSizeF size, QString direction, QSizeF fieldSize, float speed, QString buttons, Entity* parent)
{
    pos.setY(pos.y() - size.height());
    Entity *e = new Entity(parent, pos, size);
    e->addComponent(new MagnetZipperComponent(convertToDirection(direction), QSizeF((0.5 + fieldSize.width()) * TILE_SIZE , fieldSize.height() * TILE_SIZE),
                                              speed, buttons));
    // e->addComponent(new DebugComponent(QColor("chartreuse"), true));

    return e;
}

Entity* EntityFactory::magnetJumper(Tiled::MapObject* object, Entity* parent)
{
    object->setY(object->y() - object->size().height());
    Entity *e = new Entity(parent, object->position(), object->size());
    e->addComponent(new MagnetJumperComponent(
                        object->propertyAsString("force").toFloat(),
                        object->rotation(),
                        object->propertyAsString("buttons")
                        )
                    );

    ImageComponent* ic = new ImageComponent(":/entities/magnet-jumper.png");
    ic->setRotation(object->rotation());
    e->addComponent(ic);

    return e;
}

Entity* EntityFactory::magnetGravity(Tiled::MapObject* object, Entity* parent)
{
    object->setY(object->y() - object->size().height());

    Entity *e = new Entity(parent, object->position(), object->size());

    float radius =  object->propertyAsString("radius").toFloat();
    e->addComponent(new MagnetGravityComponent(
                        radius,
                        object->propertyAsString("force").toFloat(),
                        object->propertyAsString("buttons")
                        )
                    );

    ImageComponent* ic = new ImageComponent(":/entities/magnet-gravity.png");
    ic->setRotation(object->rotation());
    e->addComponent(ic);

    Entity *hitboxDisplay = new Entity(
            parent, object->position() - QPointF(radius - object->size().width() / 2, radius - object->size().height() / 2),
            QSizeF(radius * 2, radius * 2));

    hitboxDisplay->addComponent(new GenericRenderComponent(&GenericRenderComponent::circleMagnetHitbox));
    hitboxDisplay->setZValue(-0.001);

    return e;
}

Entity *EntityFactory::box(Tiled::MapObject *object, Entity *parent)
{
    object->setY(object->y() - object->size().height());
    Entity *e = new Entity(parent, object->position(), object->size());

    e->addComponent(new ImageComponent(":/entities/magnet-box.png"));
    e->addComponent(new PhysicsComponent());
    e->addComponent(new MagnetZipperReactorComponent());
    e->addComponent(new MagnetJumperReactorComponent());
    e->addComponent(new MagnetGravityReactorComponent());
    e->addComponent(new MagnetGravityReactorComponent("BoxGravityHitbox", "PlayerGravityMagnet"));
    e->addComponent(new MagnetGravityComponent(40, 2, "", QPointF(), "BoxGravityHitbox", "PlayerGravityMagnet"));
    e->addComponent(new SquareHitboxComponent(GameButtonComponent::HITBOX_REACTOR_NAME));

    return e;
}

Entity *EntityFactory::graphic(Tiled::MapObject *object, Entity *parent)
{
    Entity *e = new Entity(parent, object->position(), object->size());
    if(object->propertyAsString("animationName") != "")
    {
        AnimationComponent* ac = AnimationFactory::getAnimationComponent(object->propertyAsString("animationName"));
        if(object->propertyAsString("buttons") != "")
        {
            ac->setCurrentAnimation("idle");
            ac->setButtons(object->propertyAsString("buttons"));
        }
        else
        {
            ac->setCurrentAnimation(object->propertyAsString("animationToPlay"));
        }
        e->addComponent(ac);
    }
    if(object->propertyAsString("texture") != "")
    {
        e->addComponent(new ImageComponent(object->propertyAsString("texture")));
    }
    if(object->propertyAsString("parallax") != "")
    {
        e->addComponent(new ParallaxComponent(object->propertyAsString("parallax").toFloat()));
    }
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


Input::Key EntityFactory::convertToKey(const QString& str)
{
    QString testStr(str.toUpper());

    if(testStr == "LEFT") return Input::Key::LEFT;
    else if(testStr == "RIGHT") return Input::Key::RIGHT;
    else if(testStr == "JUMP") return Input::Key::JUMP;
    else if(testStr == "INTERACT") return Input::Key::INTERACT;
    else if(testStr == "ZIP") return Input::Key::ZIP;
    else if(testStr == "NONE") return Input::Key::NONE;
}
