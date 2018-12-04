#include "playerstate.h"

void StandingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (!checkFalling(playerInputComponent))
    {
        if (game->isKeyDown(Qt::Key_Up))
        {
            playerInputComponent->setState(&PlayerState::jumping);
        }
        else if (handleHorizontalMovement(playerInputComponent, game))
        {
            playerInputComponent->setState(&PlayerState::running);
        }
    }
}

void StandingState::enter(PlayerInputComponent *playerInputComponent) const
{
    PlayerState::enter(playerInputComponent);
}
