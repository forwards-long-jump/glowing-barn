#include "playerstate.h"

void JumpingState::enter(PlayerInputComponent* playerInputComponent) const
{
    PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        physicsComponent->jump();
    }
}

void JumpingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    checkFalling(playerInputComponent);

    if (Game::input.isKeyDown(Input::ZIP))
    {
        // In prevision for later

        // if (in zipper range)
        // playerInputComponent->setState(&PlayerState::zipping);
    }

    handleHorizontalMovement(playerInputComponent);

    if (checkOnGround(playerInputComponent))
    {
        playerInputComponent->setState(&PlayerState::standing);
    }
}
