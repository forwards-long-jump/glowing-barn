#include "playerstate.h"

void JumpingState::enter(PlayerInputComponent* playerInputComponent) const
{
    PlayerState::enter(playerInputComponent);

    PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        physicsComponent->jump();
    }
}

void JumpingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    checkFalling(playerInputComponent);

    if (game->isKeyDown(Qt::Key_Space))
    {
        // In prevision for later

        // if (in zipper range)
        // playerInputComponent->setState(&PlayerState::zipping);
    }

    handleHorizontalMovement(playerInputComponent, game);
}
