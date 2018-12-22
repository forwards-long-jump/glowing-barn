#include "include/hitboxreactorcomponent.h"

void HitboxReactorComponent::update()
{
    for (auto hb : HitboxComponent::getInstancesOf(targetName))
    {
        if (hitbox.intersects(hb))
        {
            onIntersect(hb);
        }
    }
}

void HitboxReactorComponent::init()
{
    hitbox.assignParent(entity);
    hitbox.init();
}

void HitboxReactorComponent::setHitboxOffset(float dx, float dy)
{
    hitbox.setOffset(dx, dy);
}

void HitboxReactorComponent::setHitboxSize(float w, float h)
{
    hitbox.setSize(w, h);
}
