#include "include/playerinputcomponent.h"

PlayerInputComponent::PlayerInputComponent()
{
    setState(&standing);
}

void PlayerInputComponent::handleInput()
{
    state->handleInput(this, static_cast<Scene*>(entity->scene())->getGame());
}

void PlayerInputComponent::update()
{
    handleInput();
    state->update(this, static_cast<Scene*>(entity->scene())->getGame());
}
