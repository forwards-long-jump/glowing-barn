#include "magnetgravityreactorcomponent.h"

MagnetGravityReactorComponent::MagnetGravityReactorComponent(QString hitboxName, QString magnetGravityComponentName, QString name)
    : HitboxReactorComponent(hitboxName, name),
      magnetGravityComponentName(magnetGravityComponentName)
{

}

void MagnetGravityReactorComponent::init()
{
    setHitbox(new SquareHitboxComponent());
}

void MagnetGravityReactorComponent::onIntersect(HitboxComponent* hb)
{
    CircleHitboxComponent* magneticFieldHitboxComponent = static_cast<CircleHitboxComponent*>(hb);

    // Prevents interactions with self
    if(magneticFieldHitboxComponent->getParent() == this->getParent()) return;

    // Get the associated MagnetJumperComponent to get magnet settings
    MagnetGravityComponent* magnetGravityComponent  = dynamic_cast<MagnetGravityComponent*>(magneticFieldHitboxComponent->getParent()->getComponent(magnetGravityComponentName));
    assert(magnetGravityComponent);

    PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(getParent()->getComponent("PhysicsComponent"));
    if(physicsComponent)
    {

        // Vector between player center and magnet center
        float vx = (getParent()->x() + getParent()->getSize().width() / 2) - hb->getCenter().x();
        float vy = (getParent()->y() + getParent()->getSize().height() / 2) - hb->getCenter().y();
        float d = qSqrt(vx * vx + vy * vy);
        // Force is normalised to make it feel the same for different sized magnets
        float f = magnetGravityComponent->getForce() / (d / magneticFieldHitboxComponent->getRadius());


        if(d < 20 && magnetGravityComponent->getForce() < 0)
        {
            int tick = static_cast<GameScene*>(getParent()->scene())->getGame()->getTick();
            physicsComponent->setSpeed(0, 0);
            physicsComponent->disablePhysicsForTick();
            getParent()->setPos(hb->getCenter() - QPointF(getParent()->getSize().width() / 2,
                                                          getParent()->getSize().height() / 2 + qSin(tick * 0.07) * 2));
        }
        else if(qAbs(d) > 0.001)
        {
            physicsComponent->setSpeed(physicsComponent->getSpeed().x() + f * (vx / d),
                                             physicsComponent->getSpeed().y() + f * (vy / d));
        }
    }
}
