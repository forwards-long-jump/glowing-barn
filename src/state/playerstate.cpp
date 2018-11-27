#include "include/playerstate.h"

#include <QDebug>

void RunningState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    qDebug() << "à l'écoute";
    if (game->isKeyDown(Qt::Key_Up))
    {
        qDebug() << "saut";
        playerInputComponent->setState(&playerInputComponent->jumping);
    }
}

void RunningState::update(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Left))
    {
        dx -= 1;
        if (dx < - maxDx) dx = - maxDx;
    }
    if (game->isKeyDown(Qt::Key_Right))
    {
        dx += 1;
        if (dx > maxDx) dx = maxDx;
    }

    playerInputComponent->getEntity()->setX(playerInputComponent->getEntity()->x() + dx);
}

void StandingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    qDebug() << "à l'écoute";
    if (game->isKeyDown(Qt::Key_Up))
    {
        qDebug() << "saut";
        playerInputComponent->setState(&playerInputComponent->jumping);
    }
}

void StandingState::update(PlayerInputComponent* playerInputComponent, Game* game)
{
    if      (dx > 0) dx --;
    else if (dx < 0) dx ++;

    playerInputComponent->getEntity()->setX(playerInputComponent->getEntity()->x() + dx);
}

void JumpingState::handleInput(PlayerInputComponent* playerInputComponent, Game* game)
{
    if (game->isKeyDown(Qt::Key_Space))
    {
        // if (in zipper range)
        // playerInputComponent->setState(&PlayerState::zipping);
    }
}

void JumpingState::update(PlayerInputComponent* playerInputComponent, Game* game)
{
    dy = 2 * maxHeight / (timeToMaxHeight * timeToMaxHeight) * (timeToMaxHeight - timer);
    if      (dy > maxDy) dy = maxDy;
    else if (dy < - maxDy) dy = - maxDy;

    if (game->isKeyDown(Qt::Key_Left))
    {
        dx -= 1;
        if (dx < - maxDx) dx = - maxDx;
    }
    if (game->isKeyDown(Qt::Key_Right))
    {
        dx += 1;
        if (dx > maxDx) dx = maxDx;
    }

    playerInputComponent->getEntity()->setX(playerInputComponent->getEntity()->x() + dx);
    playerInputComponent->getEntity()->setY(playerInputComponent->getEntity()->y() + dy);
}

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent, Game *game)
{

}

void ZippingState::update(PlayerInputComponent* playerInputComponent, Game* game)
{

}
