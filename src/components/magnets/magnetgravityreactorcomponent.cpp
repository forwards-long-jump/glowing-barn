#include "magnetgravityreactorcomponent.h"

MagnetGravityReactorComponent::MagnetGravityReactorComponent(QString name) : HitboxReactorComponent(MagnetGravityComponent::HITBOX_NAME, name)
{

}

void MagnetGravityReactorComponent::init()
{
    setHitbox(new SquareHitboxComponent());
}

void MagnetGravityReactorComponent::onIntersect(HitboxComponent *hb)
{
    CircleHitboxComponent* magneticFieldHitboxComponent = static_cast<CircleHitboxComponent*>(hb);

    // Get the associated MagnetJumperComponent to get magnet settings
    MagnetGravityComponent *magnetJumperComponent  = static_cast<MagnetGravityComponent*>(magneticFieldHitboxComponent->getEntity()->getComponent("MagnetGravityComponent"));
    assert(magnetJumperComponent);

    PhysicsComponent *physicsComponent = dynamic_cast<PhysicsComponent*>(getEntity()->getComponent("PhysicsComponent"));
    if(physicsComponent)
    {

        // Vector between player center and magnet center
        float vx = (getEntity()->x() + getEntity()->getSize().width() / 2) - hb->getCenter().x();
        float vy = (getEntity()->y() + getEntity()->getSize().height() / 2) - hb->getCenter().y();
        float d = qSqrt(vx * vx + vy * vy);
        // Force is normalised to make it feel the same for different sized magnets
        float f = magnetJumperComponent->getForce() / (d / magneticFieldHitboxComponent->getRadius());

        physicsComponent->setSpeed(physicsComponent->getSpeed().x() + f * (vx / d),
                                         physicsComponent->getSpeed().y() + f * (vy / d));
    }
}
