#include "include/doorcomponent.h"

void DoorComponent::action(Entity *target) const
{
    // TODO destroy current lever and load next one / credits
}

void DoorComponent::init()
{
    InteractiveComponent::init();

    setHitbox(new SquareHitboxComponent());
}
