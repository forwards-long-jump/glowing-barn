#include "playerstate.h"

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    if (Game::input.isKeyDown(Input::ZIP))
    {
        playerInputComponent->setState(&PlayerState::falling);
    }

    if (Game::input.isKeyDown(Input::LEFT))
    {
        setHeadingRight(false);
    }

    if (Game::input.isKeyDown(Input::RIGHT))
    {
        setHeadingRight(true);
    }
}

void ZippingState::enter(PlayerInputComponent *playerInputComponent) const
{
    // TODO
    // change player sprite
    // play sound ...
}

void ZippingState::setHeadingRight(bool headingRight_)
{
    PlayerState::setHeadingRight(headingRight_);
    // TODO
    // change player sprite
}
