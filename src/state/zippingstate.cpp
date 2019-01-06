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

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    PhysicsComponent* pc = dynamic_cast<PhysicsComponent*>(playerInputComponent->getParent()->getComponent("PhysicsComponent"));
    MagnetZipperReactorComponent* mzrc = dynamic_cast<MagnetZipperReactorComponent*>(playerInputComponent->getParent()->getComponent("MagnetZipperReactorComponent"));

    int targetRotation = 0;

    if(ac && pc && mzrc)
    {
        switch(mzrc->getCurrentDirection())
        {
        case MagnetZipperComponent::DIRECTION::DOWN:
            targetRotation = 0;
            break;
        case MagnetZipperComponent::DIRECTION::UP:
            targetRotation = 180;
            break;
        case MagnetZipperComponent::DIRECTION::LEFT:
            setHeadingRight(false, playerInputComponent);
            targetRotation = -90;
            break;
        case MagnetZipperComponent::DIRECTION::RIGHT:
            setHeadingRight(false, playerInputComponent);
            targetRotation = 90;
            break;
        }

        ac->setRotation(ac->getRotation() + (targetRotation - ac->getRotation()) * 0.2);
    }
}

void ZippingState::enter(PlayerInputComponent* playerInputComponent) const
{
    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("zipping");
    }
}

void ZippingState::setHeadingRight(bool headingRight_, PlayerInputComponent* playerInputComponent)
{
    PlayerState::setHeadingRight(headingRight_, playerInputComponent);
}
