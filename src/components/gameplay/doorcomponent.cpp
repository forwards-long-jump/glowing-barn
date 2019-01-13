#include "include/doorcomponent.h"

void DoorComponent::action(Entity* target)
{
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

void DoorComponent::update()
{
    InteractiveComponent::update();
    if(requiredButtons.length() > 0)
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

DoorComponent::DoorComponent(QString targetMap_, QString targetDoor_, QString requiredButtons_, bool isFinalDoor_, Input::Key key_, QString name_)
    : InteractiveComponent(key_, name_, "InteractiveHitboxComponent", requiredButtons_)
{
    targetMap = targetMap_;
    targetDoor = targetDoor_;

    isFinalDoor = isFinalDoor_;
}

void DoorComponent::init()
{
    InteractiveComponent::init();

    setHitbox(new SquareHitboxComponent());
}
