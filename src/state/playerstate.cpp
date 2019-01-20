#include "include/playerstate.h"

StandingState PlayerState::standing;
RunningState PlayerState::running;
SkiddingState PlayerState::skidding;
JumpingState PlayerState::jumping;
FallingState PlayerState::falling;
ZippingState PlayerState::zipping;
DeadState PlayerState::dying;

bool PlayerState::headingRight = true;
int PlayerState::ticksSinceEntering = 0;

/**
 * @brief PlayerState::handleHorizontalMovement
 * @param playerInputComponent
 * @return
 */
bool PlayerState::handleHorizontalMovement(PlayerInputComponent* playerInputComponent)
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getParent()->getComponent("PhysicsComponent"));
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

/**
 * @brief PlayerState::setHeadingRight
 * @param headingRight_
 * @param playerInputComponent
 */
void PlayerState::setHeadingRight(bool headingRight_, PlayerInputComponent* playerInputComponent)
{
    headingRight = headingRight_;
    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setMirrored(!headingRight_);
    }
}

/**
 * @brief PlayerState::checkFalling
 * @param playerInputComponent
 * @return
 */
bool PlayerState::checkFalling(PlayerInputComponent* playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getParent()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr && physicsComponent->isFalling())
    {
        playerInputComponent->setState(&PlayerState::falling);
        return true;
    }
    return false;
}

/**
 * @brief PlayerState::checkOnGround
 * @param playerInputComponent
 * @return
 */
bool PlayerState::checkOnGround(PlayerInputComponent* playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getParent()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
        return physicsComponent->isOnGround();
    return false;
}

/**
 * @brief PlayerState::checkNoSpeed
 * @param playerInputComponent
 * @return
 */
bool PlayerState::checkNoSpeed(PlayerInputComponent* playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getParent()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
        return physicsComponent->hasZeroSpeed();
    return true;
}
