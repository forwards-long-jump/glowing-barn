#include "playerstate.h"

void StandingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Up))
    {
        playerInputComponent->setState(&PlayerState::jumping);
    }

    if (handleHorizontalMovement(playerInputComponent, game))
    {
        playerInputComponent->setState(&PlayerState::running);
    }
}
