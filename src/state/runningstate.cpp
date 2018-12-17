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
    // TODO
    // change player sprite
}

void RunningState::setHeadingRight(bool headingRight_)
{
    PlayerState::setHeadingRight(headingRight_);
    // TODO
    // change player sprite
}
