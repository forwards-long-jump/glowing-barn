#include "playerstate.h"

/**
 * @brief SkiddingState::handleInput
 * @param playerInputComponent
 */
void SkiddingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    ticksSinceEntering++;

    if (!checkFalling(playerInputComponent))
    {
        if (handleHorizontalMovement(playerInputComponent))
        {
            playerInputComponent->setState(&PlayerState::running);
        }

        if (checkNoSpeed(playerInputComponent))
        {
            playerInputComponent->setState(&PlayerState::standing);
        }

        if (Game::input.isKeyDown(Input::JUMP))
        {
            playerInputComponent->setState(&PlayerState::jumping);
        }
    }
}

/**
 * @brief SkiddingState::enter
 * @param playerInputComponent
 */
void SkiddingState::enter(PlayerInputComponent* playerInputComponent) const
{
    ticksSinceEntering = 0;
    PlayerState::falling.setLenient(true);

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("skidding");
    }
}
