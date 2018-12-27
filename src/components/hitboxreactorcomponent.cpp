#include "include/hitboxreactorcomponent.h"

void HitboxReactorComponent::update()
{
    for (auto hb : HitboxComponent::getInstancesOf(targetName))
    {
        if (hitbox->intersects(hb))
        {
            onIntersect(hb);
        }
    }
}

void HitboxReactorComponent::init()
{

}

void HitboxReactorComponent::setHitbox(HitboxComponent *hb)
{
    hitbox = hb;
    hitbox->assignParent(entity);
    hitbox->init();
}
