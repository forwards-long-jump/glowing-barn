#include "interactivecomponent.h"
#include "animationcomponent.h"

InteractiveComponent::InteractiveComponent(Input::Key key_, QString name_, QString targetHitboxName)
    : HitboxReactorComponent(targetHitboxName, name_),
    key(key_)
{
    readyToInteract = false;
    removePromptOnNextTick = false;

}

void InteractiveComponent::init()
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

void InteractiveComponent::update()
{
    HitboxReactorComponent::update();
    if (removePromptOnNextTick)
    {
        commandPrompt->disableComponent("AnimationComponent");
    }
    removePromptOnNextTick = true;
}

void InteractiveComponent::onIntersect(HitboxComponent* hb)
{
    InteractiveHitboxComponent* ihb = static_cast<InteractiveHitboxComponent*> (hb);
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

void InteractiveComponent::showPrompt() const
{
    commandPrompt->enableComponent("AnimationComponent");
}
