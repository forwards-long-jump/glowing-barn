#include "include/doorcomponent.h"

void DoorComponent::action(Entity *target)
{
   target->disableComponent("PhysicsComponent");
    static_cast<AnimationComponent*>(target->getComponent("AnimationComponent"))->setCurrentAnimation("door");
    static_cast<AnimationComponent*>(target->getComponent("AnimationComponent"))->disableLooping();
    target->disableComponent("PlayerInputComponent");

    static_cast<GameScene*>(target->scene())->scheduleMapChange(targetMap, targetDoor);
}

DoorComponent::DoorComponent(QString targetMap_, QString targetDoor_, Input::Key key_, QString name_) : InteractiveComponent(key_, name_)
{
    targetMap = targetMap_;
    targetDoor = targetDoor_;
}

void DoorComponent::init()
{
    InteractiveComponent::init();

    setHitbox(new SquareHitboxComponent());
}
