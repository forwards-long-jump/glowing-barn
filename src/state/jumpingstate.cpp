#include "playerstate.h"

void JumpingState::enter(PlayerInputComponent* playerInputComponent)
{
    PlayerState::enter(playerInputComponent);

    // TODO : give entitiy vertical speed
}

void JumpingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Space))
    {
        // In prevision for later

        // if (in zipper range)
        // playerInputComponent->setState(&PlayerState::zipping);
    }

    handleHorizontalMovement(playerInputComponent, game);
}
