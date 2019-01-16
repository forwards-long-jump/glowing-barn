#include "interactivereactorcomponent.h"
#include "animationcomponent.h"
#include "gamebuttoncomponent.h"

InteractiveReactorComponent::InteractiveReactorComponent(Input::Key key_, QString name_, QString targetHitboxName, QString requiredButtons_)
    : HitboxReactorComponent(targetHitboxName, name_),
    key(key_)
{
    readyToInteract = false;
    removePromptOnNextTick = false;

    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
}

void InteractiveReactorComponent::init()
{
    HitboxReactorComponent::init();

    commandPrompt = new Entity(parent->parentItem(), QSizeF(8, 8));
    QVector<QPair<QString, QVector<float>>> animations;
    AnimationComponent::addAnimationToVector("down", 2, 10, animations);
    AnimationComponent::addAnimationToVector("left", 2, 10, animations);
    AnimationComponent::addAnimationToVector("right", 2, 10, animations);
    AnimationComponent::addAnimationToVector("up", 2, 10, animations);
    commandPrompt->addComponent(new AnimationComponent(":/interface/arrowkeys.png", 16, animations));
    commandPrompt->setPos(
        parent->pos().x() + (parent->getSize().width() - commandPrompt->getSize().width()) / 2,
        parent->pos().y() - 1.5 * commandPrompt->getSize().height());
    commandPrompt->disableComponent("AnimationComponent");
}

void InteractiveReactorComponent::update()
{
    HitboxReactorComponent::update();
    if (removePromptOnNextTick)
    {
        commandPrompt->disableComponent("AnimationComponent");
    }
    removePromptOnNextTick = true;
}

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

void InteractiveReactorComponent::showPrompt() const
{
    commandPrompt->enableComponent("AnimationComponent");
}
