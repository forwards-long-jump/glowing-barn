#include "sparkcomponent.h"

const QString SparkComponent::HITBOX_REACTOR_NAME = "SparkComponent";

SparkComponent::SparkComponent(float radius, QString additionalHitboxName_, QString name) : HitboxReactorComponent(SparkComponent::HITBOX_REACTOR_NAME, name), radius(radius)
{
    additionalHitboxName = additionalHitboxName_;
}

void SparkComponent::init()
{
    CircleHitboxComponent *ch = new CircleHitboxComponent();
    setHitbox(ch);
    ch->setRadius(radius);

    if(additionalHitboxName != "")
    {
        entity->addComponent(new SquareHitboxComponent(additionalHitboxName));
    }
}

void SparkComponent::onIntersect(HitboxComponent *hb)
{
    if(hb->getEntity()->getComponent("MagnetZipperReactorComponent"))
    {
        playerInSight = true;

        QPointF playerPos = hb->getEntity()->pos();
        static_cast<AnimationComponent*>(getEntity()->getComponent("AnimationComponent"))->setCurrentAnimation("move");

        getEntity()->setX(getEntity()->x() * 0.9 + playerPos.x() * 0.1);
        getEntity()->setY(getEntity()->y() * 0.9 + playerPos.y() * 0.1);
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
