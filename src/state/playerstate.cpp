#include "include/playerstate.h"

StandingState PlayerState::standing;
RunningState PlayerState::running;
SkiddingState PlayerState::skidding;
JumpingState PlayerState::jumping;
ZippingState PlayerState::zipping;

bool PlayerState::handleHorizontalMovement(PlayerInputComponent *playerInputComponent, Game *game) const
{
    if (game->isKeyDown(Qt::Key_Left))
    {
        // TODO : move entity left

    }
    else if (game->isKeyDown(Qt::Key_Right))
    {
        // TODO : move entity right
    }
    else
    {
        return true;
    }
    return false;
}

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent, Game *game)
{
    // nothing yet
}
