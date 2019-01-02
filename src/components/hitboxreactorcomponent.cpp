#include "include/hitboxreactorcomponent.h"

void HitboxReactorComponent::update()
{
    // HitboxReactor must know its own hitbox, don't forget to call setHitbox first if you get a segfault here
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
