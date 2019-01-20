#include "interactivecomponent.h"

const QString InteractiveComponent::HITBOX_NAME = "InteractiveHitbox";

/**
 * @brief InteractiveComponent::InteractiveComponent
 * @param name_
 */
InteractiveComponent::InteractiveComponent(QString name_)
    : SquareHitboxComponent(name_)
{
    isKeyActive = false;
}

/**
 * @brief InteractiveComponent::update
 */
void InteractiveComponent::update()
{
    isKeyActive = false;
}

/**
 * @brief InteractiveComponent::askKey
 * @param key
 */
void InteractiveComponent::askKey(Input::Key key)
{
    askedKey = key;
}

