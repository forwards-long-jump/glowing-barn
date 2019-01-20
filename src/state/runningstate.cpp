#include "playerstate.h"

/**
 * @brief RunningState::handleInput
 * @param playerInputComponent
 */
void RunningState::handleInput(PlayerInputComponent* playerInputComponent)
{
    ticksSinceEntering++;

    if (!checkFalling(playerInputComponent))
    {
        if (Game::input.isKeyDown(Input::JUMP))
        {
            playerInputComponent->setState(&PlayerState::jumping);
        }

        if (!handleHorizontalMovement(playerInputComponent))
        {
            playerInputComponent->setState(&PlayerState::skidding);
        }
    }
}

/**
 * @brief RunningState::enter
 * @param playerInputComponent
 */
void RunningState::enter(PlayerInputComponent* playerInputComponent) const
{
    ticksSinceEntering = 0;
    PlayerState::falling.setLenient(true);

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("running");
    }
}
