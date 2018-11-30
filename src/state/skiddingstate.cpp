#include "playerstate.h"

void SkiddingState::handleInput(PlayerInputComponent *playerInputComponent, Game *game)
{
    if (handleHorizontalMovement(playerInputComponent, game))
    {
        playerInputComponent->setState(&PlayerState::running);
    }

    if (game->isKeyDown(Qt::Key_Up))
    {
        playerInputComponent->setState(&PlayerState::jumping);
    }
}
