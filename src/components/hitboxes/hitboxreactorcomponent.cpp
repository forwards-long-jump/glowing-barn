#include "include/hitboxreactorcomponent.h"

void HitboxReactorComponent::update()
{
    for (auto hb : HitboxComponent::getInstancesOf(targetName))
    {
        // HitboxReactor must know its own hitbox, don't forget to call setHitbox first if you get a segfault here
        if (hitbox->intersects(hb))
        {
            onIntersect(hb);
        }
    }
}

void HitboxReactorComponent::init()
{

}

void HitboxReactorComponent::setHitbox(HitboxComponent* hb)
{
    hitbox = hb;
    hitbox->setParent(parent);
    hitbox->init();
}
