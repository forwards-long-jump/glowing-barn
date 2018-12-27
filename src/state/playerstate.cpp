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
        setHeadingRight(false, playerInputComponent);
    }
    else if (Game::input.isKeyDown(Input::RIGHT))
    {
        setHeadingRight(true, playerInputComponent);
    }
    else
    {
        return false;
    }
    return true;
}

void PlayerState::setHeadingRight(bool headingRight_, PlayerInputComponent *playerInputComponent)
{
    headingRight = headingRight_;
    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getEntity()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setMirrored(!headingRight_);
    }
}

bool PlayerState::checkFalling(PlayerInputComponent *playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr && physicsComponent->isFalling())
    {
        playerInputComponent->setState(&PlayerState::falling);
        return true;
    }
    return false;
}

bool PlayerState::checkOnGround(PlayerInputComponent *playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
        return physicsComponent->isOnGround();
    return false;
}

bool PlayerState::checkNoSpeed(PlayerInputComponent *playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
        return physicsComponent->hasZeroSpeed();
    return true;
}
