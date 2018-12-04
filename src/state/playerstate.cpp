#include "include/playerstate.h"

StandingState PlayerState::standing;
RunningState PlayerState::running;
SkiddingState PlayerState::skidding;
JumpingState PlayerState::jumping;
FallingState PlayerState::falling;
ZippingState PlayerState::zipping;
bool PlayerState::headingRight = true;


bool PlayerState::handleHorizontalMovement(PlayerInputComponent *playerInputComponent, Game *game)
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        physicsComponent->setLeft(game->isKeyDown(Qt::Key_Left));
        physicsComponent->setRight(game->isKeyDown(Qt::Key_Right));
    }

    if (game->isKeyDown(Qt::Key_Left))
    {
        headingRight = false;
    }
    else if (game->isKeyDown(Qt::Key_Right))
    {
        headingRight = true;
    }
    else
    {
        return true;
    }
    return false;
}

bool PlayerState::checkFalling(PlayerInputComponent *playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr && physicsComponent->isFalling())
    {
        playerInputComponent->setState(&PlayerState::falling);
    }
}

void PlayerState::enter(PlayerInputComponent *playerInputComponent) const
{
    Component* physicsComponent = (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        dynamic_cast<PhysicsComponent*> (physicsComponent)->setFriction(friction);
    }
}

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent, Game *game)
{
    // nothing yet
}
