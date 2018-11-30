#include "include/playerstate.h"

StandingState PlayerState::standing;
RunningState PlayerState::running;
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

void RunningState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Up))
    {
        playerInputComponent->setState(&PlayerState::jumping);
    }
    else
    {
        if (!handleHorizontalMovement(playerInputComponent, game))
        {
            playerInputComponent->setState(&PlayerState::standing);
        }
    }
}

void StandingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Up))
    {
        playerInputComponent->setState(&PlayerState::jumping);
    }
    else
    {
        // TODO : decelerate entity

        if (game->isKeyDown(Qt::Key_Left) || game->isKeyDown(Qt::Key_Right))
        {
            playerInputComponent->setState(&PlayerState::running);
        }
    }
}

void JumpingState::enter(PlayerInputComponent* playerInputComponent)
{
    PlayerState::enter(playerInputComponent);
    // TODO : give entitiy vertical speed
}

void JumpingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Space))
    {
        // if (in zipper range)
        // playerInputComponent->setState(&PlayerState::zipping);
    }
    if (!handleHorizontalMovement(playerInputComponent, game))
    {
        // TODO : decelerate entity
    }
}

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent, Game *game)
{

}
