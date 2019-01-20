#include "storymagnetcomponent.h"

/**
 * @brief StoryMagnetComponent::StoryMagnetComponent
 * @param requiredButtons
 * @param targetMap
 */
StoryMagnetComponent::StoryMagnetComponent(QString requiredButtons_, QString targetMap_)
    : HitboxReactorComponent(InteractiveComponent::HITBOX_NAME, "StoryMagnetComponent"),
      targetMap(targetMap_)
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
}

/**
 * @brief StoryMagnetComponent::update
 */
void StoryMagnetComponent::update()
{
    HitboxReactorComponent::update();
    if(GameButtonComponent::areButtonsPressed(requiredButtons) && !alreadyActivated)
    {
        parent->enableComponent("PhysicsComponent");
    }
}

/**
 * @brief StoryMagnetComponent::init
 */
void StoryMagnetComponent::init()
{
    SquareHitboxComponent* hb = new SquareHitboxComponent();
    setHitbox(hb);
    hb->setOffset(0, -15);

    parent->addComponent(new PhysicsComponent(0, 0, 0, 0, 0.3, 7));
    parent->disableComponent("PhysicsComponent");
}

/**
 * @brief StoryMagnetComponent::onIntersect
 * @param hitbox
 */
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
