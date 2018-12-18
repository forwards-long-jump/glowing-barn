#include "playerstate.h"

void JumpingState::enter(PlayerInputComponent* playerInputComponent) const
{
    PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        physicsComponent->jump();
    }

    // TODO
    // change player sprite
    // play sound ...
}

void JumpingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    checkFalling(playerInputComponent);

    handleHorizontalMovement(playerInputComponent);

    if (checkOnGround(playerInputComponent))
    {
        playerInputComponent->setState(&PlayerState::standing);
    }
}

void JumpingState::setHeadingRight(bool headingRight_)
{
    PlayerState::setHeadingRight(headingRight_);
    // TODO
    // change player sprite
}
