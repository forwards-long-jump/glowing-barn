#include "playerstate.h"

void FallingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    if (Game::input.isKeyDown(Input::ZIP))
    {
        // In prevision for later

        // if (in zipper range)
        // playerInputComponent->setState(&PlayerState::zipping);
    }

    handleHorizontalMovement(playerInputComponent);
}

void FallingState::enter(PlayerInputComponent *playerInputComponent) const
{
    PlayerState::enter(playerInputComponent);
}
