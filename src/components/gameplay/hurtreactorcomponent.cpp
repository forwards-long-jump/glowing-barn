#include "hurtreactorcomponent.h"

const QString HurtReactorComponent::HITBOX_REACTOR_NAME = "HurtHitbox";

/**
 * @brief HurtReactorComponent::HurtReactorComponent
 * @param resetMap Whether the map should be reloaded on contact
 * @param name
 */
HurtReactorComponent::HurtReactorComponent(bool resetMap, QString name)
    : HitboxReactorComponent(HurtReactorComponent::HITBOX_REACTOR_NAME, name),
    resetMap(resetMap) {}

/**
 * @brief HurtReactorComponent::init
 * Important to call this function, if you want to avoid segmentation faults
 */
void HurtReactorComponent::init()
{
    setHitbox(new SquareHitboxComponent());
}

/**
 * @brief HurtReactorComponent::onIntersect
 * @param hitboxComponent
 */
void HurtReactorComponent::onIntersect(HitboxComponent* hitboxComponent)
{
    if(died) return;
    died = true;

    PlayerInputComponent* pic = dynamic_cast<PlayerInputComponent*>(parent->getComponent("PlayerInputComponent"));

    if(pic)
    {
        pic->setState(&PlayerState::dying);
        parent->disableComponent("PlayerInputComponent");
        parent->disableComponent("MagnetZipperReactorComponent");
    }

    if(resetMap)
    {
        static_cast<GameScene*>(getParent()->scene())->scheduleMapChange();
    }
}

/**
 * @brief HurtReactorComponent::isDead
 * @return
 */
bool HurtReactorComponent::isDead() const
{
    return died;
}
