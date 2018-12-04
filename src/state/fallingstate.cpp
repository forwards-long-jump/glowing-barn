#include "playerstate.h"

void FallingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Space))
    {
        // In prevision for later

        // if (in zipper range)
        // playerInputComponent->setState(&PlayerState::zipping);
    }

    handleHorizontalMovement(playerInputComponent, game);
}

void FallingState::enter(PlayerInputComponent *playerInputComponent) const
{
    PlayerState::enter(playerInputComponent);
}
