#include "playerstate.h"

/**
 * @brief FallingState::handleInput
 * @param playerInputComponent
 */
void FallingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    ticksSinceEntering++;
    handleHorizontalMovement(playerInputComponent);

    if (checkOnGround(playerInputComponent))
    {
        playerInputComponent->setState(&PlayerState::standing);
    }

    if (canBeLenient && ticksSinceEntering < jumpLeniency && Game::input.isKeyDown(Input::JUMP))
    {
        playerInputComponent->setState(&PlayerState::jumping);
    }
}

/**
 * @brief FallingState::enter
 * @param playerInputComponent
 */
void FallingState::enter(PlayerInputComponent* playerInputComponent) const
{
    ticksSinceEntering = 0;

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("falling");
    }
}

/**
 * @brief FallingState::setLenient
 * @param lenient
 */
void FallingState::setLenient(bool lenient)
{
    canBeLenient = lenient;
}
