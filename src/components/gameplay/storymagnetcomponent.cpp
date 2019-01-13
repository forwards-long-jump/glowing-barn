#include "include/storymagnetcomponent.h"

StoryMagnetComponent::StoryMagnetComponent(QString requiredButtons_, QString targetMap_)
    : HitboxReactorComponent("InteractiveHitboxComponent", "StoryMagnetComponent"),
      targetMap(targetMap_)
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
}

void StoryMagnetComponent::update()
{
    HitboxReactorComponent::update();
    if(GameButtonComponent::areButtonsPressed(requiredButtons) && !alreadyActivated)
    {
        parent->enableComponent("PhysicsComponent");
    }
}

void StoryMagnetComponent::init()
{
    SquareHitboxComponent* hb = new SquareHitboxComponent();
    setHitbox(hb);
    hb->setOffset(0, -15);

    parent->addComponent(new PhysicsComponent(0, 0, 0, 0, 0.3, 7));
    parent->disableComponent("PhysicsComponent");
}

void StoryMagnetComponent::onIntersect(HitboxComponent* hb)
{
    if (GameButtonComponent::areButtonsPressed(requiredButtons) && !alreadyActivated)
    {
        alreadyActivated = true;
        parent->disableComponent("PhysicsComponent");

        Sounds::playSound("crash");

        static_cast<GameScene*>(parent->scene())->scheduleMapChange(targetMap, "default");
    }
}
