#include "playerstate.h"

void RunningState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (!checkFalling(playerInputComponent))
    {
        if (game->isKeyDown(Qt::Key_Up))
        {
            playerInputComponent->setState(&PlayerState::jumping);
        }

        if (!handleHorizontalMovement(playerInputComponent, game))
        {
            playerInputComponent->setState(&PlayerState::skidding);
        }
    }
}

void RunningState::enter(PlayerInputComponent *playerInputComponent) const
{
    PlayerState::enter(playerInputComponent);
}
