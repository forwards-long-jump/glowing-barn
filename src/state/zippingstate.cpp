#include "playerstate.h"

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    if (Game::input.isKeyDown(Input::ZIP))
    {
        playerInputComponent->setState(&PlayerState::falling);
    }

    if (Game::input.isKeyDown(Input::LEFT))
    {
        setHeadingRight(false, playerInputComponent);
    }

    if (Game::input.isKeyDown(Input::RIGHT))
    {
        setHeadingRight(true, playerInputComponent);
    }
}

void ZippingState::enter(PlayerInputComponent *playerInputComponent) const
{
    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getEntity()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("zipping");
    }
}

void ZippingState::setHeadingRight(bool headingRight_, PlayerInputComponent *playerInputComponent)
{
    PlayerState::setHeadingRight(headingRight_, playerInputComponent);
}
