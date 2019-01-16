#include "playerstate.h"

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

void FallingState::enter(PlayerInputComponent* playerInputComponent) const
{
    ticksSinceEntering = 0;

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("falling");
    }
}

void FallingState::setHeadingRight(bool headingRight_, PlayerInputComponent* playerInputComponent)
{
    PlayerState::setHeadingRight(headingRight_, playerInputComponent);
    // TODO
    // change player sprite
}

void FallingState::setLenient(bool lenient)
{
    canBeLenient = lenient;
}
