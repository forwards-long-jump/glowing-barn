#include "include/playerinputcomponent.h"
#include "scene.h"

void PlayerInputComponent::update()
{
    state->handleInput(this, static_cast<Scene*>(entity->scene())->getGame());
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
