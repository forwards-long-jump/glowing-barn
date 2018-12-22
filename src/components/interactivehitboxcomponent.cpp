#include "include/interactivehitboxcomponent.h"

InteractiveHitboxComponent::InteractiveHitboxComponent(QString name_)
    :HitboxComponent(name_)
{
    isKeyActive = false;
}

void InteractiveHitboxComponent::update()
{
    isKeyActive = false;
}

void InteractiveHitboxComponent::askKey(Input::Key key)
{
    askedKey = key;
}

