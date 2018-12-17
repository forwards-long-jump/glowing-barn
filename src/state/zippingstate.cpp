#include "playerstate.h"

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    if (Game::input.isKeyDown(Input::ZIP))
    {
        playerInputComponent->setState(&PlayerState::falling);
    }
}

void ZippingState::enter(PlayerInputComponent *playerInputComponent) const
{
    // TODO
    // change player sprite
    // play sound ...
}
