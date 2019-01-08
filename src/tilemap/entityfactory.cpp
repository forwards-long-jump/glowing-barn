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
    player->addComponent(new MagnetGravityComponent(50, -0.85, "", QPointF(0, -20), "BoxGravityHitbox", "PlayerGravityMagnet"));
    player->addComponent(new SquareHitboxComponent(GameButtonComponent::HITBOX_REACTOR_NAME));
    player->addComponent(new SquareHitboxComponent(SparkComponent::HITBOX_REACTOR_NAME));
    player->addComponent(new PlayerInputComponent());
    player->addComponent(new PhysicsComponent());
    player->addComponent(new HurtReactorComponent());
    player->addComponent(new MagnetZipperReactorComponent());
    player->addComponent(new MagnetJumperReactorComponent());
    player->addComponent(new MagnetGravityReactorComponent());
    player->addComponent(animationComponent);

    // Magnet enabled / disabled particles
    player->addComponent(new ParticleSpawnerComponent(
                             [](QPainter* painter, Particle* particle) {
                             if(particle->getIndex() % 2 == 0)
                             {
                                 painter->fillRect(0, 0, 2, 2, QColor(248, 0, 67, (particle->getLifetime() / 30.0) * 255));
                             }
                             else
                             {
                                 painter->fillRect(0, 0, 2, 2, QColor(0, 145, 228, (particle->getLifetime() / 30.0) * 255));
                             }
                         }, [](Particle* particle) {
                          particle->setPos(particle->pos() + QPointF(particle->getDx() + qSin(0.1 * particle->getLifetime() + particle->getIndex()) * 0.2, particle->getDy()));
    }, "MagnetParticleSpawner"));

    player->addComponent(new GenericRenderComponent(
                             [](QPainter* p, Entity* e, int tick) {

                             if(e->getComponent("MagnetZipperReactorComponent"))
                             {
                                // TODO: Cleanup this
                                ParticleSpawnerComponent* magnetParticleSpawner = static_cast<ParticleSpawnerComponent*>(e->getComponent("MagnetParticleSpawner"));
                                AnimationComponent* ac = static_cast<AnimationComponent*>(e->getComponent("AnimationComponent"));

                                 if(tick % 4 == 0)
                                 {
                                     if(ac->getMirrored())
                                     {
                                         magnetParticleSpawner->spawn(e->x() + e->getSize().width() * 0.75, e->y() + 5, qSin(tick) * 0.1, qSin(tick) * 0.1 - 0.3, 2, 2, 30);
                                         magnetParticleSpawner->spawn(e->x() + e->getSize().width() * 0.18, e->y() + 5, qSin(tick) * 0.1, qSin(tick) * 0.1 - 0.3, 2, 2, 30);
                                     }
                                     else
                                     {
                                         magnetParticleSpawner->spawn(e->x() + e->getSize().width() * 0.18, e->y() + 5, qSin(tick) * 0.1, qSin(tick) * 0.1 - 0.3, 2, 2, 30);
                                         magnetParticleSpawner->spawn(e->x() + e->getSize().width() * 0.75, e->y() + 5, qSin(tick) * 0.1, qSin(tick) * 0.1 - 0.3, 2, 2, 30);
                                     }
                                 }
                             }
                         }
                         ));


    return player;
}

Entity* EntityFactory::playerCredits(QPointF pos, QSizeF size, Entity* parent)
{
    Entity* playerCredits = new Entity(parent, pos, size);

    AnimationComponent* animationComponent = AnimationFactory::getAnimationComponent("player");
    animationComponent->setCurrentAnimation("running");
    playerCredits->addComponent(animationComponent);

    return playerCredits;
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
    spark->addComponent(chc);
    chc->setRadius(object->size().width() * 0.8);

    return spark;
}

Entity* EntityFactory::collision(QPointF pos, QSizeF size, Entity* parent)
{
    Entity* e = new Entity(parent, pos, size);
    e->addComponent(new SquareHitboxComponent("WallComponent"));
    return e;
}

Entity* EntityFactory::gameButton(Tiled::MapObject* object, Entity* parent)
{
    Entity* e = new Entity(parent, object->position(), object->size());

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
    Entity* e = new Entity(parent, object->position() - QPointF(0, 6), object->size() + QSizeF(0, 12));
    e->addComponent(new DoorComponent(object->propertyAsString("targetMap"), object->propertyAsString("targetSpawn"), object->propertyAsString("buttons")));

    // The door animation has a bigger size, so we create a new component for it
    AnimationComponent* ac = AnimationFactory::getAnimationComponent("door");
    ac->setCurrentAnimation("idle");
    ac->setButtons("auto_door");
    e->addComponent(ac);
    e->addComponent(new ParallaxComponent(0.0001));
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
    Entity* e = new Entity(parent, pos, size);
    e->addComponent(new MagnetZipperComponent(convertToDirection(direction), QSizeF((0.5 + fieldSize.width()) * TILE_SIZE , fieldSize.height() * TILE_SIZE),
                                              speed, buttons));
    // e->addComponent(new DebugComponent(QColor("chartreuse"), true));

    return e;
}

Entity* EntityFactory::magnetJumper(Tiled::MapObject* object, Entity* parent)
{
    object->setY(object->y() - object->size().height());
    Entity* e = new Entity(parent, object->position(), object->size());
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

    Entity* e = new Entity(parent, object->position(), object->size());

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

    Entity* hitboxDisplay = new Entity(
            e, - QPointF(radius - object->size().width() / 2, radius - object->size().height() / 2),
            QSizeF(radius * 2, radius * 2));

    hitboxDisplay->addComponent(new GenericRenderComponent(&GenericRenderComponent::circleMagnetHitbox));
    hitboxDisplay->setZValue(-0.001);

    return e;
}

Entity* EntityFactory::box(Tiled::MapObject* object, Entity* parent)
{
    object->setY(object->y() - object->size().height());
    Entity* e = new Entity(parent, object->position(), object->size());

    e->addComponent(new ImageComponent(":/entities/magnet-box.png"));
    e->addComponent(new PhysicsComponent());
    e->addComponent(new MagnetZipperReactorComponent());
    e->addComponent(new MagnetJumperReactorComponent());
    e->addComponent(new MagnetGravityReactorComponent());
    e->addComponent(new MagnetGravityReactorComponent("BoxGravityHitbox", "PlayerGravityMagnet", ""));
    e->addComponent(new MagnetGravityComponent(40, 2, "", QPointF(), "BoxGravityHitbox", "PlayerGravityMagnet"));
    e->addComponent(new SquareHitboxComponent(GameButtonComponent::HITBOX_REACTOR_NAME));

    return e;
}

Entity* EntityFactory::soundButtonReactor(Tiled::MapObject* object, Entity* parent)
{
    Entity* e = new Entity(parent, object->position(), object->size());
    e->addComponent(new SoundButtonReactorComponent(object->propertyAsString("start"),
                                                    object->propertyAsString("end"),
                                                    object->propertyAsString("idle"),
                                                    object->propertyAsString("loop"),
                                                    object->propertyAsString("buttons")));
    return e;
}

Entity* EntityFactory::graphic(Tiled::MapObject* object, Entity* parent)
{
    Entity* e = new Entity(parent, object->position(), object->size());
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
