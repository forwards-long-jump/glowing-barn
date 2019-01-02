#include "magnetzipperreactorcomponent.h"

MagnetZipperReactorComponent::MagnetZipperReactorComponent(QString name) : HitboxReactorComponent(MagnetZipperComponent::HITBOX_NAME, name)
{

}

void MagnetZipperReactorComponent::init()
{
    setHitbox(new SquareHitboxComponent());
}

void MagnetZipperReactorComponent::onIntersect(HitboxComponent *hb)
{
    // Zipper magnets should only have square hitboxes
    SquareHitboxComponent* magneticFieldHitboxComponent = static_cast<SquareHitboxComponent*>(hb);

    // Get the associated MagnetZipperComponent to get magnet settings
    MagnetZipperComponent *magnetZipperComponent = static_cast<MagnetZipperComponent*>(magneticFieldHitboxComponent->getEntity()->getComponent("MagnetZipperComponent"));
    assert(magnetZipperComponent);

    PhysicsComponent *physicsComponent = dynamic_cast<PhysicsComponent*>(getEntity()->getComponent("PhysicsComponent"));
    PlayerInputComponent *playerInputComponent = dynamic_cast<PlayerInputComponent*>(getEntity()->getComponent("PlayerInputComponent"));

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
    float dx, dy = 0;
    switch(magnetZipperComponent->getDirection())
    {
    case MagnetZipperComponent::DIRECTION::DOWN:
        getEntity()->setY(getEntity()->y() - magnetZipperComponent->getSpeed());
        dy = - magnetZipperComponent->getSpeed();
        break;
    case MagnetZipperComponent::DIRECTION::UP:
        getEntity()->setY(getEntity()->y() + magnetZipperComponent->getSpeed());
        dy = magnetZipperComponent->getSpeed();
        break;
    case MagnetZipperComponent::DIRECTION::LEFT:
        getEntity()->setX(getEntity()->x() + magnetZipperComponent->getSpeed());
        dx = magnetZipperComponent->getSpeed();
        break;
    case MagnetZipperComponent::DIRECTION::RIGHT:
        getEntity()->setX(getEntity()->x() - magnetZipperComponent->getSpeed());
        dx = - magnetZipperComponent->getSpeed();
        break;
    }

    // Center the player with a spring effect in the middle of the magnetic field
    switch(magnetZipperComponent->getDirection())
    {
    case MagnetZipperComponent::DIRECTION::DOWN:
    case MagnetZipperComponent::DIRECTION::UP:
    {
        float dist = (magneticFieldHitboxComponent->getHitbox().x() + magneticFieldHitboxComponent->getHitbox().width() / 2) - (getEntity()->x() + getEntity()->getSize().width() / 2);
        zipperDx += dist * ZIPPER_DISTANCE_ACCELERATION;
    }
        break;
    case MagnetZipperComponent::DIRECTION::LEFT:
    case MagnetZipperComponent::DIRECTION::RIGHT:
    {
        float dist = (magneticFieldHitboxComponent->getHitbox().y() + magneticFieldHitboxComponent->getHitbox().height() / 2) - (getEntity()->y() + getEntity()->getSize().height() / 2);
        zipperDy += dist * ZIPPER_DISTANCE_ACCELERATION;
    }
        break;
    }

    // Apply spring effect
    zipperDx *= ZIPPER_FRICTION;
    zipperDy *= ZIPPER_FRICTION;
    getEntity()->setX(getEntity()->x() + zipperDx);
    getEntity()->setY(getEntity()->y() + zipperDy);

    // Disable gravity if entity has a physic component
    if(physicsComponent)
    {
        physicsComponent->setSpeed(dx + zipperDx, dy + zipperDy);
        physicsComponent->disablePhysicsForTick();
    }

    // Handle reseting values when the entity leaves the magnetic area
    if(!magneticFieldHitboxComponent->getHitbox().intersects(QRectF(entity->pos(), entity->getSize()))) {
        zipperDx = 0;
        zipperDy = 0;
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
