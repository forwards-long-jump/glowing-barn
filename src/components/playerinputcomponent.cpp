#include "include/playerinputcomponent.h"
#include "scene.h"

PlayerInputComponent::PlayerInputComponent()
{
    setState(&PlayerState::standing);
}

void PlayerInputComponent::update()
{
    state->handleInput(this, static_cast<Scene*>(entity->scene())->getGame());
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
