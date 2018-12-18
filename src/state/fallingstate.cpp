#include "playerstate.h"

void FallingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    handleHorizontalMovement(playerInputComponent);

    if (checkOnGround(playerInputComponent))
    {
        playerInputComponent->setState(&PlayerState::standing);
    }

    if (Game::input.isKeyDown(Input::JUMP) && playerInputComponent->isJumpLenient())
    {
        playerInputComponent->setState(&PlayerState::jumping);
    }
}

void FallingState::enter(PlayerInputComponent *playerInputComponent) const
{
    // TODO
    // change player sprite
}

void FallingState::setHeadingRight(bool headingRight_)
{
    PlayerState::setHeadingRight(headingRight_);
    // TODO
    // change player sprite
}
