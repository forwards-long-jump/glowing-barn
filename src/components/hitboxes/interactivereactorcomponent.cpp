#include "interactivereactorcomponent.h"

InteractiveReactorComponent::InteractiveReactorComponent(QString name_)
    :SquareHitboxComponent(name_)
{
    isKeyActive = false;
}

void InteractiveReactorComponent::update()
{
    isKeyActive = false;
}

void InteractiveReactorComponent::askKey(Input::Key key)
{
    askedKey = key;
}

