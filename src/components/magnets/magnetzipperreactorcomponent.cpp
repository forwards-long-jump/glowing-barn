#include "magnetzipperreactorcomponent.h"

MagnetZipperReactorComponent::MagnetZipperReactorComponent(QString name) : HitboxReactorComponent(MagnetZipperComponent::HITBOX_NAME, name)
{

}

void MagnetZipperReactorComponent::init()
{
    setHitbox(new SquareHitboxComponent());
}

void MagnetZipperReactorComponent::onIntersect(HitboxComponent* hb)
{
    isInAnyField = true;
    assert(hitbox);

    // Zipper magnets should only have square hitboxes
    SquareHitboxComponent* magneticFieldHitboxComponent = static_cast<SquareHitboxComponent*>(hb);

    // Get the associated MagnetZipperComponent to get magnet settings
    MagnetZipperComponent* magnetZipperComponent = static_cast<MagnetZipperComponent*>(magneticFieldHitboxComponent->getParent()->getComponent("MagnetZipperComponent"));
    assert(magnetZipperComponent);

    PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(getParent()->getComponent("PhysicsComponent"));
    PlayerInputComponent* playerInputComponent = dynamic_cast<PlayerInputComponent*>(getParent()->getComponent("PlayerInputComponent"));

    // Make the entity entrance smoother by keeping its last dx/dy
    if(physicsComponent)
    {

        if(zipperFirstEntrance) {
            zipperFirstEntrance = false;
            zipperDx = physicsComponent->getSpeed().x() * ZIPPER_FRICTION;
            zipperDy = physicsComponent->getSpeed().y() * ZIPPER_FRICTION;
        }
    }

    // Set player state to zipping if it has a playerInput
    if(playerInputComponent)
    {
        playerInputComponent->setState(&PlayerState::zipping);
    }

    // Move entity, save dx/dy for the PhysicsComponent when exiting the area
    float dx = 0, dy = 0;
    switch(magnetZipperComponent->getDirection())
    {
    case MagnetZipperComponent::DIRECTION::DOWN:
        getParent()->setY(getParent()->y() - magnetZipperComponent->getSpeed());
        dy = - magnetZipperComponent->getSpeed();
        break;
    case MagnetZipperComponent::DIRECTION::UP:
        getParent()->setY(getParent()->y() + magnetZipperComponent->getSpeed());
        dy = magnetZipperComponent->getSpeed();
        break;
    case MagnetZipperComponent::DIRECTION::LEFT:
        getParent()->setX(getParent()->x() + magnetZipperComponent->getSpeed());
        dx = magnetZipperComponent->getSpeed();
        break;
    case MagnetZipperComponent::DIRECTION::RIGHT:
        getParent()->setX(getParent()->x() - magnetZipperComponent->getSpeed());
        dx = - magnetZipperComponent->getSpeed();
        break;
    }

    currentDirection = magnetZipperComponent->getDirection();

    // Center the player with a spring effect in the middle of the magnetic field
    switch(magnetZipperComponent->getDirection())
    {
    case MagnetZipperComponent::DIRECTION::DOWN:
    case MagnetZipperComponent::DIRECTION::UP:
    {
        float dist = (magneticFieldHitboxComponent->getHitbox().x() + magneticFieldHitboxComponent->getHitbox().width() / 2) - (getParent()->x() + getParent()->getSize().width() / 2);
        zipperDx += dist * ZIPPER_DISTANCE_ACCELERATION;
    }
        break;
    case MagnetZipperComponent::DIRECTION::LEFT:
    case MagnetZipperComponent::DIRECTION::RIGHT:
    {
        float dist = (magneticFieldHitboxComponent->getHitbox().y() + magneticFieldHitboxComponent->getHitbox().height() / 2) - (getParent()->y() + getParent()->getSize().height() / 2);
        zipperDy += dist * ZIPPER_DISTANCE_ACCELERATION;
    }
        break;
    }

    // Apply spring effect
    zipperDx *= ZIPPER_FRICTION;
    zipperDy *= ZIPPER_FRICTION;
    getParent()->setX(getParent()->x() + zipperDx);
    getParent()->setY(getParent()->y() + zipperDy);

    // Disable gravity if entity has a physic component
    if(physicsComponent)
    {
        physicsComponent->setSpeed(dx + zipperDx, dy + zipperDy);
        physicsComponent->disablePhysicsForTick();
    }

    // Handle reseting values when the entity leaves the magnetic area
    if(!magneticFieldHitboxComponent->getHitbox().intersects(QRectF(parent->pos(), parent->getSize()))) {
        zipperDx = 0;
        zipperDy = 0;
        if(playerInputComponent)
            playerInputComponent->setState(&PlayerState::falling);
        zipperFirstEntrance = true;
    }
}

void MagnetZipperReactorComponent::onEnable()
{
    zipperDx = 0;
    zipperDy = 0;
    zipperFirstEntrance = true;
}

void MagnetZipperReactorComponent::update()
{
    isInAnyField = false;

    HitboxReactorComponent::update();

    if(!isInAnyField)
    {
        PlayerInputComponent* playerInputComponent = dynamic_cast<PlayerInputComponent*>(getParent()->getComponent("PlayerInputComponent"));
        if(playerInputComponent)
        {
            if(playerInputComponent->getState() == &PlayerState::zipping)
            {
                playerInputComponent->setState(&PlayerState::falling);
            }
        }
    }
}

MagnetZipperComponent::DIRECTION MagnetZipperReactorComponent::getCurrentDirection() const
{
    return currentDirection;
}
