#include "magnetjumperreactorcomponent.h"

MagnetJumperReactorComponent::MagnetJumperReactorComponent(QString name) : HitboxReactorComponent(MagnetJumperComponent::HITBOX_NAME, name)
{

}

void MagnetJumperReactorComponent::init()
{
    setHitbox(new SquareHitboxComponent());
}

void MagnetJumperReactorComponent::onIntersect(HitboxComponent* hb)
{
    // Zipper magnets should only have square hitboxes
    SquareHitboxComponent* magneticFieldHitboxComponent = static_cast<SquareHitboxComponent*>(hb);

    // Get the associated MagnetJumperComponent to get magnet settings
    MagnetJumperComponent* magnetJumperComponent  = static_cast<MagnetJumperComponent*>(magneticFieldHitboxComponent->getParent()->getComponent("MagnetJumperComponent"));
    assert(magnetJumperComponent);

    PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(getParent()->getComponent("PhysicsComponent"));
    if(physicsComponent)
    {
        physicsComponent->disablePhysicsForTick();
        physicsComponent->setForcedSpeed(qSin(qDegreesToRadians(magnetJumperComponent->getRotation())) * magnetJumperComponent->getForce(),
                                   -qCos(qDegreesToRadians(magnetJumperComponent->getRotation())) * magnetJumperComponent->getForce(), 0.9, 0.94);
    }
}
