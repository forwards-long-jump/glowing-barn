#include "hitboxreactorcomponent.h"

/**
 * @brief HitboxReactorComponent::update
 * Imperatively needs setHitbox() to be called before update() is called
 * Typically setHitbox() is called in the init() method
 */
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

/**
 * @brief HitboxReactorComponent::setHitbox
 * @param hb
 */
void HitboxReactorComponent::setHitbox(HitboxComponent* hb)
{
    hitbox = hb;
    hitbox->setParent(parent);
    hitbox->init();
}
