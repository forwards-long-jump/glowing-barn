#include "playerstate.h"

/**
 * @brief JumpingState::enter
 * @param playerInputComponent
 */
void JumpingState::enter(PlayerInputComponent* playerInputComponent) const
{
    ticksSinceEntering = 0;
    PlayerState::falling.setLenient(false);

    PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*> (playerInputComponent->getParent()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        physicsComponent->jump();
    }

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("jumping");
    }
}

/**
 * @brief JumpingState::handleInput
 * @param playerInputComponent
 */
void JumpingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    ticksSinceEntering++;
    if (ticksSinceEntering < nbTicksJumping && Game::input.isKeyDown(Input::JUMP))
    {
        PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*> (playerInputComponent->getParent()->getComponent("PhysicsComponent"));
        if (physicsComponent != nullptr)
        {
            physicsComponent->jump();
        }
    }

    checkFalling(playerInputComponent);

    handleHorizontalMovement(playerInputComponent);

    if (checkOnGround(playerInputComponent))
    {
        playerInputComponent->setState(&PlayerState::standing);
    }
}

