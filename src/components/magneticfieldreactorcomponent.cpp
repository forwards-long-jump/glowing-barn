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

/**
* @brief MagneticFieldReactorComponent::handleZipperMagnet
* @param hitboxComponent
*/
void MagneticFieldReactorComponent::handleZipperMagnet(HitboxComponent *hitboxComponent)
{
    // Check if the entity is in the magnetic "field"
    if(hitboxComponent->getHitbox().intersects(QRectF(entity->pos(), entity->getSize())))
    {
        // Get the associated ZipperMagnetComponent
        ZipperMagnetComponent *zipperMagnet = static_cast<ZipperMagnetComponent*>(hitboxComponent->getEntity()->getComponent("ZipperMagnetComponent"));
        assert(zipperMagnet);

        // Disable gravity if entity has a physic component
        PhysicsComponent *physicsComponent = dynamic_cast<PhysicsComponent*>(getEntity()->getComponent("PhysicsComponent"));
        if(physicsComponent)
        {
            physicsComponent->disableGravityForTick();
        }

        // Set player state to zipping if it has a playerInput
        PlayerInputComponent *playerInput = dynamic_cast<PlayerInputComponent*>(getEntity()->getComponent("PlayerInputComponent"));
        if(playerInput)
        {
            playerInput->setState(&PlayerState::zipping);
        }

        // Move player
        switch(zipperMagnet->getDirection())
        {
        case ZipperMagnetComponent::DIRECTION::DOWN:
            getEntity()->setY(getEntity()->y() + zipperMagnet->getSpeed());
            break;
        case ZipperMagnetComponent::DIRECTION::UP:
             getEntity()->setY(getEntity()->y() - zipperMagnet->getSpeed());
            break;
        case ZipperMagnetComponent::DIRECTION::LEFT:
            getEntity()->setX(getEntity()->x() + zipperMagnet->getSpeed());
            break;
        case ZipperMagnetComponent::DIRECTION::RIGHT:
            getEntity()->setX(getEntity()->x() - zipperMagnet->getSpeed());
            break;
        }
    }
}
