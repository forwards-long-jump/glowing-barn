#include "hurtreactorcomponent.h"

const QString HurtReactorComponent::HITBOX_REACTOR_NAME = "HurtHitbox";

HurtReactorComponent::HurtReactorComponent(bool resetMap, QString name) :
    HitboxReactorComponent(HurtReactorComponent::HITBOX_REACTOR_NAME, name),
    resetMap(resetMap) {}

void HurtReactorComponent::init()
{
    setHitbox(new SquareHitboxComponent());
}

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

bool HurtReactorComponent::isDead() const
{
    return died;
}
