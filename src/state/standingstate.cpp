#include "playerstate.h"

/**
 * @brief StandingState::handleInput
 * @param playerInputComponent
 */
void StandingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    ticksSinceEntering++;

    if (!checkFalling(playerInputComponent))
    {
        if (Game::input.isKeyDown(Input::JUMP))
        {
            playerInputComponent->setState(&PlayerState::jumping);
        }
        else if (handleHorizontalMovement(playerInputComponent))
        {
            playerInputComponent->setState(&PlayerState::running);
        }
    }
}

/**
 * @brief StandingState::enter
 * @param playerInputComponent
 */
void StandingState::enter(PlayerInputComponent* playerInputComponent) const
{
    ticksSinceEntering = 0;
    PlayerState::falling.setLenient(true);

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("standing");
    }
}
