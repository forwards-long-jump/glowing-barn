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

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getEntity()->getComponent("AnimationComponent"));
    PhysicsComponent* pc = dynamic_cast<PhysicsComponent*>(playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    MagnetZipperReactorComponent* mzrc = dynamic_cast<MagnetZipperReactorComponent*>(playerInputComponent->getEntity()->getComponent("MagnetZipperReactorComponent"));

    if(ac && pc && mzrc)
    {
        switch(mzrc->getCurrentDirection())
        {
        case MagnetZipperComponent::DIRECTION::DOWN:
            ac->setRotation(0);
            break;
        case MagnetZipperComponent::DIRECTION::UP:
            ac->setRotation(180);
            break;
        case MagnetZipperComponent::DIRECTION::LEFT:
            setHeadingRight(false, playerInputComponent);
            ac->setRotation(-90);
            break;
        case MagnetZipperComponent::DIRECTION::RIGHT:
            setHeadingRight(false, playerInputComponent);
            ac->setRotation(90);
            break;
        }

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
