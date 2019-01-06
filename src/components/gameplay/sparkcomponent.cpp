#include "sparkcomponent.h"

const QString SparkComponent::HITBOX_REACTOR_NAME = "SparkComponent";

SparkComponent::SparkComponent(float radius, QString additionalHitboxName_, QString name) : HitboxReactorComponent(SparkComponent::HITBOX_REACTOR_NAME, name), radius(radius)
{
    additionalHitboxName = additionalHitboxName_;
}

void SparkComponent::init()
{
    CircleHitboxComponent* ch = new CircleHitboxComponent();
    setHitbox(ch);
    ch->setRadius(radius);

    if(additionalHitboxName != "")
    {
        parent->addComponent(new SquareHitboxComponent(additionalHitboxName));
    }
}

void SparkComponent::onIntersect(HitboxComponent* hb)
{
    if(hb->getParent()->getComponent("MagnetZipperReactorComponent"))
    {
        playerInSight = true;

        QPointF playerPos = hb->getParent()->pos();
        static_cast<AnimationComponent*>(getParent()->getComponent("AnimationComponent"))->setCurrentAnimation("move");

        getParent()->setX(getParent()->x() * 0.9 + playerPos.x() * 0.1);
        getParent()->setY(getParent()->y() * 0.9 + playerPos.y() * 0.1);
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
        static_cast<AnimationComponent*>(getParent()->getComponent("AnimationComponent"))->setCurrentAnimation("idle");
}
