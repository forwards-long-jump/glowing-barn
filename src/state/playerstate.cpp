#include "include/playerstate.h"

StandingState PlayerState::standing;
RunningState PlayerState::running;
SkiddingState PlayerState::skidding;
JumpingState PlayerState::jumping;
FallingState PlayerState::falling;
ZippingState PlayerState::zipping;
bool PlayerState::headingRight = true;


bool PlayerState::handleHorizontalMovement(PlayerInputComponent *playerInputComponent)
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        physicsComponent->setLeft(Game::input.isKeyDown(Input::LEFT));
        physicsComponent->setRight(Game::input.isKeyDown(Input::RIGHT));
    }

    if (Game::input.isKeyDown(Input::LEFT))
    {
        headingRight = false;
    }
    else if (Game::input.isKeyDown(Input::RIGHT))
    {
        headingRight = true;
    }
    else
    {
        return false;
    }
    return true;
}

bool PlayerState::checkFalling(PlayerInputComponent *playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr && physicsComponent->isFalling())
    {
        playerInputComponent->setState(&PlayerState::falling);
    }
}

bool PlayerState::checkOnGround(PlayerInputComponent *playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
        return physicsComponent->isOnGround();
}

bool PlayerState::checkNoSpeed(PlayerInputComponent *playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
        return physicsComponent->hasZeroSpeed();
}
