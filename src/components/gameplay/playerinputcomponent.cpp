#include "playerinputcomponent.h"
#include "scene.h"

void PlayerInputComponent::update()
{
    DebugComponent* d = dynamic_cast<DebugComponent*>(entity->getComponent("DebugComponent"));
    if(d) {
        if (state == &PlayerState::standing)
        {
            d->setDebugText("standing");
        }
        if (state == &PlayerState::running)
        {
            d->setDebugText("running");
        }
        if (state == &PlayerState::skidding)
        {
            d->setDebugText("skidding");
        }
        if (state == &PlayerState::jumping)
        {
            d->setDebugText("jumping");
        }
        if (state == &PlayerState::falling)
        {
            d->setDebugText("falling");
        }
        if (state == &PlayerState::zipping)
        {
            d->setDebugText("zipping");
        }
    }

    // Handle magnet activation
    if(Game::input.isKeyDown(Input::ZIP))
    {
        if(releasedKeyAfterTogglingMagnet)
        {
            releasedKeyAfterTogglingMagnet = false;
            // Toggle all magnetic components here
            // NOTE: We mostly use the magnetZipper to check if any magnet is enabled
            if(!entity->disableComponent("MagnetZipperReactorComponent"))
            {
                Sounds::playSound("magnetOn");
                entity->enableComponent("MagnetZipperReactorComponent");
            }
            else
            {
                Sounds::playSound("magnetOff");
            }

            if(!entity->disableComponent("MagnetJumperReactorComponent")) entity->enableComponent("MagnetJumperReactorComponent");
            if(!entity->disableComponent("MagnetGravityReactorComponent")) entity->enableComponent("MagnetGravityReactorComponent");
            // Player magnet sources
            if(!entity->disableComponent("PlayerGravityMagnet")) entity->enableComponent("PlayerGravityMagnet");
        }
    }
    else
    {
        releasedKeyAfterTogglingMagnet = true;
    }

    // Handle contextual interactions
    interactiveHitbox.setActive(Game::input.isKeyDown(interactiveHitbox.getAskedKey()));

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(getEntity()->getComponent("AnimationComponent"));
    PhysicsComponent* pc = dynamic_cast<PhysicsComponent*>(getEntity()->getComponent("PhysicsComponent"));

    if(ac && pc && getState() != &PlayerState::zipping)
    {
        int targetRotation = -qAbs(pc->getSpeed().x());
        ac->setRotation(ac->getRotation() + (targetRotation - ac->getRotation()) * 0.5);
    }

    // Handle states input
    state->handleInput(this);
}

void PlayerInputComponent::init()
{
    interactiveHitbox.assignParent(entity);
    interactiveHitbox.init();
    setState(&PlayerState::standing);
}

PlayerState* PlayerInputComponent::getState() const
{
    return state;
}

void PlayerInputComponent::setState(PlayerState* _state)
{
    if(state != _state)
    {
        state = _state;
        state->enter(this);
    }
}
