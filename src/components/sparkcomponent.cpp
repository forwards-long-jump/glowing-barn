#include "sparkcomponent.h"

const QString SparkComponent::HITBOX_REACTOR_NAME = "SparkComponent";

SparkComponent::SparkComponent(QString name) : HitboxReactorComponent(SparkComponent::HITBOX_REACTOR_NAME, name)
{

}

void SparkComponent::init()
{
    CircleHitboxComponent *ch = new CircleHitboxComponent();
    setHitbox(ch);
    ch->setRadius(50);
}

void SparkComponent::onIntersect(HitboxComponent *hb)
{
    if(hb->getEntity()->getComponent("MagnetZipperReactorComponent"))
    {
        playerInSight = true;

        QPointF playerPos = hb->getEntity()->pos();
        static_cast<AnimationComponent*>(getEntity()->getComponent("AnimationComponent"))->setCurrentAnimation("move");

        getEntity()->setX(getEntity()->x() + (playerPos.x()-getEntity()->x()) * 0.1);
        getEntity()->setY(getEntity()->y() + (playerPos.y()-getEntity()->y()) * 0.1);
    }
}

void SparkComponent::onEnable()
{

}

void SparkComponent::update()
{
    playerInSight = false;

    HitboxReactorComponent::update();

    if(!playerInSight)
        static_cast<AnimationComponent*>(getEntity()->getComponent("AnimationComponent"))->setCurrentAnimation("idle");
}
