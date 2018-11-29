#include "include/playerstate.h"

StandingState PlayerState::standing;
RunningState PlayerState::running;
JumpingState PlayerState::jumping;
ZippingState PlayerState::zipping;

void RunningState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Up))
    {
        playerInputComponent->setState(&PlayerState::jumping);
    }
    else
    {
        if (game->isKeyDown(Qt::Key_Left))
        {
            playerInputComponent->getEntity()->addDdx(- ddx);
        }
        else if (game->isKeyDown(Qt::Key_Right))
        {
            playerInputComponent->getEntity()->addDdx(ddx);
        }
        else
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
        float dx = playerInputComponent->getEntity()->getDx();
        // these are the brakes
        playerInputComponent->getEntity()->addDdx( - dx / 2);

        if (game->isKeyDown(Qt::Key_Left) || game->isKeyDown(Qt::Key_Right))
        {
            playerInputComponent->setState(&PlayerState::running);
        }
    }
}

void JumpingState::enter(PlayerInputComponent* playerInputComponent)
{
    PlayerState::enter(playerInputComponent);
    playerInputComponent->getEntity()->addDdy(jumpSpeed);
}

void JumpingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Space))
    {
        // if (in zipper range)
        // playerInputComponent->setState(&PlayerState::zipping);
    }
    if (game->isKeyDown(Qt::Key_Left))
    {
        playerInputComponent->getEntity()->addDdx(- ddx);
    }
    else if (game->isKeyDown(Qt::Key_Right))
    {
        playerInputComponent->getEntity()->addDdx(ddx);
    }
    else
    {
        // gently decelerate
        float dx = playerInputComponent->getEntity()->getDx();
        playerInputComponent->getEntity()->addDdx( - dx / 1.5);
    }
}

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent, Game *game)
{

}
