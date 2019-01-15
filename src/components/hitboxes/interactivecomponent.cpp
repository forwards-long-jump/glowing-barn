#include "interactivecomponent.h"

InteractiveComponent::InteractiveComponent(QString name_)
    :SquareHitboxComponent(name_)
{
    isKeyActive = false;
}

void InteractiveComponent::update()
{
    isKeyActive = false;
}

void InteractiveComponent::askKey(Input::Key key)
{
    askedKey = key;
}

