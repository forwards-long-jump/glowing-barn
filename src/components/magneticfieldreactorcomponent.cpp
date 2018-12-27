#include "magneticfieldreactorcomponent.h"

MagneticFieldReactorComponent::MagneticFieldReactorComponent() : Component("MagneticFieldReactorComponent"){}

/**
 * @brief Looks for all HitBoxes that generate "magnetic fields" and call the right function to handle it
 */
void MagneticFieldReactorComponent::update()
{
    // Zipper magnet
    for(HitboxComponent* hitboxComponent : HitboxComponent::getInstancesOf(ZipperMagnetComponent::HITBOX_NAME))
    {
        handleZipperMagnet(hitboxComponent);
    }

    // TODO: GravityMagnet, GrapplinMagnet, ...
}

void MagneticFieldReactorComponent::onEnable()
{
    zipperDx = 0;
    zipperDy = 0;
    zipperFirstEntrance = true;
}

/**
* @brief MagneticFieldReactorComponent::handleZipperMagnet
* @param hitboxComponent
*/
void MagneticFieldReactorComponent::handleZipperMagnet(HitboxComponent *hitboxComponent)
{
    // Check if the entity is in the magnetic "field"
    if(hitboxComponent->getHitbox().intersects(QRectF(entity->pos(), entity->getSize())))
    {
        PhysicsComponent *physicsComponent = dynamic_cast<PhysicsComponent*>(getEntity()->getComponent("PhysicsComponent"));
        if(physicsComponent)
        {
            // Make the entity entrance smoother by keeping its last dx/dy
            if(zipperFirstEntrance) {
                zipperFirstEntrance = false;
                zipperDx = physicsComponent->getSpeed().x() * ZIPPER_FRICTION;
                zipperDy = physicsComponent->getSpeed().y() * ZIPPER_FRICTION;
            }
        }

        // Get the associated ZipperMagnetComponent
        ZipperMagnetComponent *zipperMagnet = static_cast<ZipperMagnetComponent*>(hitboxComponent->getEntity()->getComponent("ZipperMagnetComponent"));
        assert(zipperMagnet);

        // Set player state to zipping if it has a playerInput
        PlayerInputComponent *playerInput = dynamic_cast<PlayerInputComponent*>(getEntity()->getComponent("PlayerInputComponent"));
        if(playerInput)
        {
            playerInput->setState(&PlayerState::zipping);
        }

        // Move player, save dx/dy for the PhysicsComponent when exiting the area
        float dx, dy = 0;
        switch(zipperMagnet->getDirection())
        {
        case ZipperMagnetComponent::DIRECTION::DOWN:
            getEntity()->setY(getEntity()->y() - zipperMagnet->getSpeed());
            dy = - zipperMagnet->getSpeed();
            break;
        case ZipperMagnetComponent::DIRECTION::UP:
             getEntity()->setY(getEntity()->y() + zipperMagnet->getSpeed());
             dy = zipperMagnet->getSpeed();
            break;
        case ZipperMagnetComponent::DIRECTION::LEFT:
            getEntity()->setX(getEntity()->x() + zipperMagnet->getSpeed());
            dx = zipperMagnet->getSpeed();
            break;
        case ZipperMagnetComponent::DIRECTION::RIGHT:
            getEntity()->setX(getEntity()->x() - zipperMagnet->getSpeed());
            dx = - zipperMagnet->getSpeed();
            break;
        }

        // Center the player with a spring effect in the middle of the magnetic field
        switch(zipperMagnet->getDirection())
        {
        case ZipperMagnetComponent::DIRECTION::DOWN:
        case ZipperMagnetComponent::DIRECTION::UP:
            {
                float dist = (hitboxComponent->getHitbox().x() + hitboxComponent->getHitbox().width() / 2) - (getEntity()->x() + getEntity()->getSize().width() / 2);
                zipperDx += dist * ZIPPER_DISTANCE_ACCELERATION;
            }
            break;
        case ZipperMagnetComponent::DIRECTION::LEFT:
        case ZipperMagnetComponent::DIRECTION::RIGHT:
            {
                float dist = (hitboxComponent->getHitbox().y() + hitboxComponent->getHitbox().height() / 2) - (getEntity()->y() + getEntity()->getSize().height() / 2);
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
        if(!hitboxComponent->getHitbox().intersects(QRectF(entity->pos(), entity->getSize()))) {
            zipperDx = 0;
            zipperDy = 0;
            playerInput->setState(&PlayerState::falling);
            zipperFirstEntrance = true;
        }
    }
}
