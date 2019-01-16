#include "playerstate.h"

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

void RunningState::setHeadingRight(bool headingRight_, PlayerInputComponent* playerInputComponent)
{
    PlayerState::setHeadingRight(headingRight_, playerInputComponent);
    // TODO
    // change player sprite
}
