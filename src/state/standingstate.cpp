#include "playerstate.h"

void StandingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    if (!checkFalling(playerInputComponent))
    {
        if (Game::input.isKeyDown(Input::JUMP))
        {
            playerInputComponent->setState(&PlayerState::jumping);
        }
        else if (handleHorizontalMovement(playerInputComponent))
        {
            playerInputComponent->setState(&PlayerState::running);
        }
    }
}

void StandingState::enter(PlayerInputComponent *playerInputComponent) const
{
    // TODO
    // change player sprite
}
