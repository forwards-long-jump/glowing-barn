#include "entityfactory.h"

Entity* EntityFactory::player(Tiled::MapObject* object, Entity* parent)
{
    if (object->propertyAsString("animationName") == "playerStory")
    {
        return storyPlayer(object->position(), QSizeF(object->propertyAsString("w").toFloat(), object->propertyAsString("h").toFloat()), parent);
    }
    return player(object->position(), QSizeF(object->propertyAsString("w").toFloat(), object->propertyAsString("h").toFloat()), object->propertyAsString("animationName"), parent);
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

    const int PARTICLE_LIFE_TIME = 30;
    const int PARTICLE_SIZE = 2;

    // Magnet enabled / disabled particles
    player->addComponent(new ParticleSpawnerComponent(
                             [](QPainter* painter, Particle* particle)
                             {
                                 if(particle->getIndex() % 2 == 0)
                                 {
                                     painter->fillRect(0, 0, 2, 2, QColor(248, 0, 67, (particle->getLifetime() / static_cast<float>(PARTICLE_LIFE_TIME)) * 255));
                                 }
                                 else
                                 {
                                     painter->fillRect(0, 0, 2, 2, QColor(0, 145, 228, (particle->getLifetime() / static_cast<float>(PARTICLE_LIFE_TIME)) * 255));
                                 }
                            },
                            [](Particle* particle)
                            {
                                particle->setPos(
                                            particle->pos() +
                                            QPointF(particle->getDx() +
                                                    qSin(0.1 * particle->getLifetime()
                                                         + particle->getIndex()) * 0.2,
                                                    particle->getDy()));
                            },
                            [](Entity* e, int tick) -> QVector<ParticleParameters>
                            {

                                const float LEFT_POSITION_COEFF = 0.18;
                                const float RIGHT_POSITION_COEFF = 0.75;
                                const float FORCE_COEFF = 0.1;
                                const float SPEED_FORCE_COEEF = 0.2;
                                const float BASE_Y_FORCE = 0.3;
                                const int Y_OFFSET = 5;

                                if(e->getComponent("MagnetZipperReactorComponent"))
                                {
                                   AnimationComponent* ac = static_cast<AnimationComponent*>(e->getComponent("AnimationComponent"));
                                   PhysicsComponent* pc = static_cast<PhysicsComponent*>(e->getComponent("PhysicsComponent"));

                                    if(tick % 5 == 0)
                                    {
                                        float x1 = ac->getMirrored() ? LEFT_POSITION_COEFF : RIGHT_POSITION_COEFF;
                                        float x2 = ac->getMirrored() ? RIGHT_POSITION_COEFF : LEFT_POSITION_COEFF;

                                        x1 = e->x() + x1 * e->getSize().width();
                                        x2 = e->x() + x2 * e->getSize().width();

                                        ParticleParameters p1;
                                        p1.x = x2;
                                        p1.y = e->y() + Y_OFFSET;
                                        p1.dx = qSin(tick) * FORCE_COEFF + pc->getSpeed().x() * SPEED_FORCE_COEEF;
                                        p1.dy = qSin(tick) * FORCE_COEFF - BASE_Y_FORCE + pc->getSpeed().y() * SPEED_FORCE_COEEF;
                                        p1.w = PARTICLE_SIZE;
                                        p1.h = PARTICLE_SIZE;
                                        p1.lifetime = PARTICLE_LIFE_TIME;

                                        ParticleParameters p2;
                                        p2.x = x1;
                                        p2.y = e->y() + Y_OFFSET;
                                        p2.dx = qSin(tick) * FORCE_COEFF + pc->getSpeed().x() * SPEED_FORCE_COEEF;
                                        p2.dy = qSin(tick) * FORCE_COEFF - BASE_Y_FORCE + pc->getSpeed().y() * SPEED_FORCE_COEEF;
                                        p2.w = PARTICLE_SIZE;
                                        p2.h = PARTICLE_SIZE;
                                        p2.lifetime = PARTICLE_LIFE_TIME;


                                        QVector<ParticleParameters> v;
                                        v.append(p1);
                                        v.append(p2);
                                        return v;
                                    }
                                }

                                return QVector<ParticleParameters>();
                            },
    "MagnetParticleSpawner"));


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

Entity* EntityFactory::storyPlayer(QPointF pos, QSizeF size, Entity* parent)
{
    Entity* player = new Entity(parent, pos, size);
    AnimationComponent* animationComponent = AnimationFactory::getAnimationComponent("playerStory");
    player->addComponent(animationComponent);

    player->addComponent(new SquareHitboxComponent(GameButtonComponent::HITBOX_REACTOR_NAME));
    player->addComponent(new SquareHitboxComponent(SparkComponent::HITBOX_REACTOR_NAME));
    player->addComponent(new PlayerInputComponent());
    player->addComponent(new PhysicsComponent());
    player->addComponent(new HurtReactorComponent());

    return player;
}

Entity* EntityFactory::hurt(Tiled::MapObject* object, Entity* parent)
{
    Entity* e = new Entity(parent, object->position(), object->size());
    e->addComponent(new SquareHitboxComponent(HurtReactorComponent::HITBOX_REACTOR_NAME));
    return e;
}

Entity* EntityFactory::text(Tiled::MapObject* object, Entity* parent)
{
    Entity* e = new Entity(parent, object->position(), object->size());
    e->addComponent(new TextComponent(
                        object->propertyAsString("text"),
                        object->propertyAsString("buttons"),
                        object->propertyAsString("fontSize").toInt()
                        )
                    );
    return e;
}

Entity* EntityFactory::spark(Tiled::MapObject* object, Entity* parent)
{
    Entity* spark = new Entity(parent, object->position(), object->size());
    AnimationComponent* animationComponent = AnimationFactory::getAnimationComponent("spark");
    animationComponent->setCurrentAnimation("idle");
    spark->addComponent(animationComponent);
    spark->addComponent(new SparkComponent(object->property("radius").toFloat(), object->property("speed").toFloat(), object->propertyAsString("hitboxName")));
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
    e->addComponent(new DoorComponent(object->propertyAsString("targetMap"), object->propertyAsString("targetSpawn"), object->propertyAsString("buttons"), object->property("isFinalDoor").toBool()));

    // The door animation has a bigger size, so we create a new component for it
    AnimationComponent* ac = AnimationFactory::getAnimationComponent(object->propertyAsString("animation") != "" ? object->propertyAsString("animation") : "door");
    ac->setCurrentAnimation("idle");
    ac->setButtons("auto_door");
    if(object->property("mirrorX").toBool())
    {
        ac->setMirrored(true);
    }
    e->addComponent(ac);
    e->addComponent(new ParallaxComponent(0.0001));
    return e;
}

Entity *EntityFactory::storyActivation(Tiled::MapObject* object, Entity* parent)
{
    Entity* e = new Entity(parent, object->position(), object->size());
    e->addComponent(new StoryActivationComponent(object->propertyAsString("name")));
    return e;
}

Entity *EntityFactory::storyMagnet(Tiled::MapObject* object, Entity* parent)
{
    Entity* e = new Entity(parent, object->position(), object->size());
    e->addComponent(new StoryMagnetComponent(object->propertyAsString("buttons"), object->propertyAsString("targetMap")));
    AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnetZipper");
    ac->setCurrentAnimation("active");
    ac->setRotation(-90);
    e->addComponent(ac);
    e->setZValue(1);

    return e;
}

Entity* EntityFactory::cameraSequence(Tiled::MapObject* object, Entity* parent)
{
    Entity* cameraSequence = new Entity(parent, object->position(), object->size());
    cameraSequence->addComponent(new CameraSequenceComponent(
                                     object->propertyAsString("buttons"),
                                     object->propertyAsString("speed").toFloat(),
                                     object->propertyAsString("cancelAfter").toInt(),
                                     object->property("lockPlayerInput").toBool(),
                                     object->property("playOnce").toBool()
                                     )
                                );
    return cameraSequence;
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
    // Note: the MagnetZipperComponent adds animation itself
    e->addComponent(new MagnetZipperComponent(convertToDirection(direction), QSizeF((0.5 + fieldSize.width()) * TILE_SIZE , fieldSize.height() * TILE_SIZE),
                                              speed, buttons));


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

    const int PARTICLE_LIFE_TIME = 20;
    const int PARTICLE_SIZE = 3;

    e->addComponent(new ParticleSpawnerComponent(
                             [](QPainter* painter, Particle* particle)
                             {
                                 if(particle->getIndex() % 2 == 0)
                                 {
                                     painter->fillRect(0, 0, PARTICLE_SIZE, PARTICLE_SIZE, QColor(248, 0, 67, (particle->getLifetime() / static_cast<float>(PARTICLE_LIFE_TIME)) * 255));
                                 }
                                 else
                                 {
                                     painter->fillRect(0, 0, PARTICLE_SIZE, PARTICLE_SIZE, QColor(0, 145, 228, (particle->getLifetime() / static_cast<float>(PARTICLE_LIFE_TIME)) * 255));
                                 }
                            },
                            [](Particle* particle)
                            {
                                particle->setPos(
                                            particle->pos() +
                                            QPointF(particle->getDx(), particle->getDy()));
                            },
                            [](Entity* e, int tick) -> QVector<ParticleParameters>
                            {
                                MagnetJumperComponent* mjc = static_cast<MagnetJumperComponent*>(e->getComponent("MagnetJumperComponent"));

                                const float LEFT_POSITION_COEFF = 0.15;
                                const float RIGHT_POSITION_COEFF = 0.72;
                                const float Y_COEFF = 0.12;

                                if(tick % 5 == 0 && !mjc->isDisabled())
                                {
                                    float x1 = RIGHT_POSITION_COEFF * e->getSize().width();
                                    float x2 = LEFT_POSITION_COEFF  * e->getSize().width();
                                    float y1 = Y_COEFF * e->getSize().height();
                                    float y2 = Y_COEFF * e->getSize().height();

                                    x1 -= e->getSize().width() / 2.0 - 1;
                                    x2 -= e->getSize().width() / 2.0 - 1;
                                    y1 -= e->getSize().height() / 2.0 - 1;
                                    y2 -= e->getSize().height() / 2.0 - 1;

                                    float rad = qDegreesToRadians(mjc->getRotation());

                                    float xr1 = x1 * qCos(rad) - y1 * qSin(rad);
                                    float yr1 = y1 * qCos(rad) + x1 * qSin(rad);

                                    float xr2 = x2 * qCos(rad) - y2 * qSin(rad);
                                    float yr2 = y2 * qCos(rad) + x2 * qSin(rad);

                                    xr1 += e->getSize().width() / 2.0 - 1;
                                    xr2 += e->getSize().width() / 2.0 - 1;
                                    yr1 += e->getSize().height() / 2.0 - 1;
                                    yr2 += e->getSize().height() / 2.0 - 1;

                                    xr1 += e->x();
                                    xr2 += e->x();
                                    yr1 += e->y();
                                    yr2 += e->y();

                                    ParticleParameters p1;
                                    p1.x = xr2;
                                    p1.y = yr2;
                                    p1.dx = qSin(qDegreesToRadians(mjc->getRotation()));
                                    p1.dy = -qCos(qDegreesToRadians(mjc->getRotation()));
                                    p1.w = PARTICLE_SIZE;
                                    p1.h = PARTICLE_SIZE;
                                    p1.lifetime = PARTICLE_LIFE_TIME;

                                    ParticleParameters p2;
                                    p2.x = xr1;
                                    p2.y = yr1;
                                    p2.dx = qSin(qDegreesToRadians(mjc->getRotation()));
                                    p2.dy = -qCos(qDegreesToRadians(mjc->getRotation()));
                                    p2.w = PARTICLE_SIZE;
                                    p2.h = PARTICLE_SIZE;
                                    p2.lifetime = PARTICLE_LIFE_TIME;


                                    QVector<ParticleParameters> v;
                                    v.append(p1);
                                    v.append(p2);
                                    return v;
                                }


                                return QVector<ParticleParameters>();
                            },
    "MagnetParticleSpawner"));

    AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnetJumper");
    ac->setButtons(object->propertyAsString("buttons"));
    ac->setRotation(object->rotation());
    e->addComponent(ac);

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

    AnimationComponent* ac = AnimationFactory::getAnimationComponent("magnetGravity");
    ac->setButtons(object->propertyAsString("buttons"));
    ac->setRotation(object->rotation());
    e->addComponent(ac);

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
    // React to gravity magnets
    e->addComponent(new MagnetGravityReactorComponent());
    // React to player magnet
    e->addComponent(new MagnetGravityReactorComponent("BoxGravityHitbox", "PlayerGravityMagnet", ""));
    // Create a "player" magnetic field so other boxes don't stack
    e->addComponent(new MagnetGravityComponent(50, 0.5, "", QPointF(0, 0), "BoxGravityHitbox", "PlayerGravityMagnet"));
    e->addComponent(new SquareHitboxComponent(GameButtonComponent::HITBOX_REACTOR_NAME));
    e->addComponent(new SquareHitboxComponent("Box"));

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
        e->addComponent(new ImageComponent(object->propertyAsString("texture"), "ImageComponent", object->propertyAsString("buttons")));
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
