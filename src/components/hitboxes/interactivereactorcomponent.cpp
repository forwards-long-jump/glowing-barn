#include "interactivereactorcomponent.h"
#include "animationfactory.h"
#include "gamebuttoncomponent.h"

/**
 * @brief InteractiveReactorComponent::InteractiveReactorComponent
 * @param key_ Key used to interact
 * @param name_
 * @param targetHitboxName Name of the hitbox which may interact with this
 * @param requiredButtons_
 */
InteractiveReactorComponent::InteractiveReactorComponent(Input::Key key_, QString name_, QString targetHitboxName, QString requiredButtons_)
    : HitboxReactorComponent(targetHitboxName, name_),
    key(key_)
{
    readyToInteract = false;
    removePromptOnNextTick = false;

    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
}

/**
 * @brief InteractiveReactorComponent::init
 */
void InteractiveReactorComponent::init()
{
    commandPrompt = new Entity(parent->parentItem(), QSizeF(8, 8));
    commandPrompt->addComponent(AnimationFactory::getAnimationComponent("keyboard"));
    commandPrompt->setPos(
        parent->pos().x() + (parent->getSize().width() - commandPrompt->getSize().width()) / 2,
        parent->pos().y() - 1.5 * commandPrompt->getSize().height());
    commandPrompt->disableComponent("AnimationComponent");
}

/**
 * @brief InteractiveReactorComponent::update
 */
void InteractiveReactorComponent::update()
{
    HitboxReactorComponent::update();
    if (removePromptOnNextTick)
    {
        commandPrompt->disableComponent("AnimationComponent");
    }
    removePromptOnNextTick = true;
}

/**
 * @brief InteractiveReactorComponent::onIntersect
 * @param hitbox
 */
void InteractiveReactorComponent::onIntersect(HitboxComponent* hb)
{
    if(requiredButtons.length() == 0 || GameButtonComponent::areButtonsPressed(requiredButtons))
    {
        InteractiveComponent* ihb = dynamic_cast<InteractiveComponent*> (hb);
        if(ihb)
        {
            showPrompt();
            ihb->askKey(key);
            if ((readyToInteract && ihb->isActive()) || key == Input::Key::NONE)
            {
                this->action(hb->getParent());
                readyToInteract = false;
            }
            if (!ihb->isActive())
            {
                readyToInteract = true;
            }

            removePromptOnNextTick = false;
        }
        else
        {
            this->action(hb->getParent());
        }
    }
}

/**
 * @brief InteractiveReactorComponent::showPrompt
 */
void InteractiveReactorComponent::showPrompt() const
{
    commandPrompt->enableComponent("AnimationComponent");
}
