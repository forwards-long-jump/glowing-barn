#include "playerinputcomponent.h"
#include "scene.h"

void PlayerInputComponent::update()
{
    if (state == &PlayerState::standing)
    {
        qDebug() << "standing";
    }
    if (state == &PlayerState::running)
    {
        qDebug() << "running";
    }
    if (state == &PlayerState::skidding)
    {
        qDebug() << "skidding";
    }
    if (state == &PlayerState::jumping)
    {
        qDebug() << "jumping";
    }
    if (state == &PlayerState::falling)
    {
        qDebug() << "falling";
    }

    // Handle magnet activation
    if(Game::input.isKeyDown(Input::ZIP))
    {
        if(releasedKeyAfterTogglingMagnet)
        {
            releasedKeyAfterTogglingMagnet = false;
            // Toggle component,
            if(!entity->disableComponent("MagneticFieldReactorComponent"))
            {
                entity->enableComponent("MagneticFieldReactorComponent");
            }
        }
    }
    else
    {
        releasedKeyAfterTogglingMagnet = true;
    }

    // Handle states input
    state->handleInput(this);
}

void PlayerInputComponent::init()
{
    setState(&PlayerState::standing);
}

PlayerState* PlayerInputComponent::getState() const
{
    return state;
}

void PlayerInputComponent::setState(PlayerState* _state)
{
    state = _state;
    state->enter(this);
}
