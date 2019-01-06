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

void MagnetGravityReactorComponent::onIntersect(HitboxComponent *hb)
{
    CircleHitboxComponent* magneticFieldHitboxComponent = static_cast<CircleHitboxComponent*>(hb);

    // Prevents interactions with self
    if(magneticFieldHitboxComponent->getEntity() == this->getEntity()) return;

    // Get the associated MagnetJumperComponent to get magnet settings
    MagnetGravityComponent *magnetGravityComponent  = dynamic_cast<MagnetGravityComponent*>(magneticFieldHitboxComponent->getEntity()->getComponent(magnetGravityComponentName));
    assert(magnetGravityComponent);

    PhysicsComponent *physicsComponent = dynamic_cast<PhysicsComponent*>(getEntity()->getComponent("PhysicsComponent"));
    if(physicsComponent)
    {

        // Vector between player center and magnet center
        float vx = (getEntity()->x() + getEntity()->getSize().width() / 2) - hb->getCenter().x();
        float vy = (getEntity()->y() + getEntity()->getSize().height() / 2) - hb->getCenter().y();
        float d = qSqrt(vx * vx + vy * vy);
        // Force is normalised to make it feel the same for different sized magnets
        float f = magnetGravityComponent->getForce() / (d / magneticFieldHitboxComponent->getRadius());


        if(d < 10 && magnetGravityComponent->getForce() < 0)
        {
            int tick = static_cast<GameScene*>(getEntity()->scene())->getGame()->getTick();
            physicsComponent->setSpeed(0, 0);
            physicsComponent->disablePhysicsForTick();
            getEntity()->setPos(hb->getCenter() - QPointF(getEntity()->getSize().width() / 2,
                                                          getEntity()->getSize().height() / 2 + qSin(tick * 0.07) * 2));
        }
        else if(qAbs(d) > 0.001)
        {
            physicsComponent->setSpeed(physicsComponent->getSpeed().x() + f * (vx / d),
                                             physicsComponent->getSpeed().y() + f * (vy / d));
        }
    }
}
