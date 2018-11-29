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
