#include "playerstate.h"

void RunningState::handleInput(PlayerInputComponent* playerInputComponent)
{
    if (!checkFalling(playerInputComponent))
    {
        if (Game::input.isKeyDown(Input::JUMP))
        {
            playerInputComponent->setState(&PlayerState::jumping);
        }

        if (!handleHorizontalMovement(playerInputComponent))
        {
            playerInputComponent->setState(&PlayerState::skidding);
        }
    }
}

void RunningState::enter(PlayerInputComponent *playerInputComponent) const
{
    PlayerState::enter(playerInputComponent);
}
