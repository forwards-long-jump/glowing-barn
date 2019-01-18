#include "doorcomponent.h"

/**
 * @brief DoorComponent::DoorComponent
 * Don't forget to call init only after its parent has been set
 * @param targetMap_
 * @param targetDoor_
 * @param requiredButtons_
 * @param isFinalDoor_
 * @param key_ Input required to open
 * @param name_
 */
DoorComponent::DoorComponent(QString targetMap_, QString targetDoor_, QString requiredButtons_, bool isFinalDoor_, Input::Key key_, QString name_)
    : InteractiveReactorComponent(key_, name_, InteractiveComponent::HITBOX_NAME, requiredButtons_)
{
    targetMap = targetMap_;
    targetDoor = targetDoor_;

    isFinalDoor = isFinalDoor_;
}

/**
 * @brief DoorComponent::action
 * @param target
 */
void DoorComponent::action(Entity* target)
{
    enteringDoor = true;
    static_cast<AnimationComponent*>(parent->getComponent("AnimationComponent"))->setCurrentAnimation("start");
    static_cast<AnimationComponent*>(parent->getComponent("AnimationComponent"))->disableLooping();

    static_cast<AnimationComponent*>(target->getComponent("AnimationComponent"))->setCurrentAnimation("door");
    static_cast<AnimationComponent*>(target->getComponent("AnimationComponent"))->disableLooping();
    target->disableComponent("PlayerInputComponent");

    if (isFinalDoor)
    {
        Sounds::fadeOut(20);

        Entity* e = new Entity(nullptr, 0, 0, 1000, 1000);
        e->addComponent(new TransitionComponent(
                    [=]() {
                        static_cast<GameScene*>(target->scene())->getGame()->switchScene("credits");
                    },
                    [](QPainter* painter, const Entity* entity, int duration, int ticksPassed) {
                        painter->fillRect(0, 0, entity->getSize().width(), entity->getSize().height(),
                            QColor(0, 0, 0, 255 * static_cast<float>(ticksPassed) / duration));
                    }, 20
        ));
        static_cast<GameScene*>(target->scene())->addItem(e);
    }
    else
    {
        static_cast<GameScene*>(target->scene())->scheduleMapChange(targetMap, targetDoor);
    }
}

/**
 * @brief DoorComponent::update
 */
void DoorComponent::update()
{
    InteractiveReactorComponent::update();
    if(requiredButtons.length() > 0 && !enteringDoor)
    {
        if(!GameButtonComponent::areButtonsPressed(requiredButtons))
        {
            static_cast<AnimationComponent*>(parent->getComponent("AnimationComponent"))->setCurrentAnimation("deactivated");
            static_cast<AnimationComponent*>(parent->getComponent("AnimationComponent"))->disableLooping();
        }
        else
        {
            static_cast<AnimationComponent*>(parent->getComponent("AnimationComponent"))->setCurrentAnimation("idle");
            static_cast<AnimationComponent*>(parent->getComponent("AnimationComponent"))->disableLooping();
        }
    }
}

/**
 * @brief DoorComponent::init
 */
void DoorComponent::init()
{
    InteractiveReactorComponent::init();

    setHitbox(new SquareHitboxComponent());
}
