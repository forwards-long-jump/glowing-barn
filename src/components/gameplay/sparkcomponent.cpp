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

    actualPosition = parent->pos();
    ticksUntilMove = QRandomGenerator::global()->bounded(0, pauseDurationInTicks);
}

void SparkComponent::onIntersect(HitboxComponent* hb)
{
    if(hb->getParent()->getComponent("MagnetZipperReactorComponent"))
    {
        playerInSight = true;

        static_cast<AnimationComponent*>(getParent()->getComponent("AnimationComponent"))->setCurrentAnimation("move");

        QPointF attackVect = hb->getParent()->pos() - actualPosition;
        actualPosition += attackVect * 0.05;
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

    if (--ticksUntilMove < 1)
    {
        float theta = QRandomGenerator::global()->bounded(2 * M_PI);
        errorComponent.setX(errorRadius * qCos(theta));
        errorComponent.setY(errorRadius * qSin(theta));
        ticksUntilMove = pauseDurationInTicks;
    }

    getParent()->setPos(actualPosition + errorComponent);
}
