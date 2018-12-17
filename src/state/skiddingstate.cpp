#include "playerstate.h"

void SkiddingState::handleInput(PlayerInputComponent *playerInputComponent)
{
    if (!checkFalling(playerInputComponent))
    {
        if (handleHorizontalMovement(playerInputComponent))
        {
            playerInputComponent->setState(&PlayerState::running);
        }

        if (checkNoSpeed(playerInputComponent))
        {
            playerInputComponent->setState(&PlayerState::standing);
        }

        if (Game::input.isKeyDown(Input::JUMP))
        {
            playerInputComponent->setState(&PlayerState::jumping);
        }
    }
}

void SkiddingState::enter(PlayerInputComponent *playerInputComponent) const
{

}
