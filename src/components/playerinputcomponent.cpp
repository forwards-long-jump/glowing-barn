#include "playerinputcomponent.h"
#include "scene.h"

void PlayerInputComponent::update()
{
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
