#include "interactivecomponent.h"
#include "animationcomponent.h"

InteractiveComponent::InteractiveComponent(Input::Key key_, QString name_)
    :HitboxReactorComponent("InteractiveHitboxComponent", name_),
    key(key_)
{
    readyToInteract = false;
    removePromptOnNextTick = false;

}

void InteractiveComponent::init()
{
    HitboxReactorComponent::init();

    commandPrompt = new Entity(nullptr, QSizeF(8, 8));
    entity->scene()->addItem(commandPrompt);
    QVector<QPair<QString, QVector<float>>> animations;
    AnimationComponent::addAnimationToVector("down", 2, 10, animations);
    AnimationComponent::addAnimationToVector("left", 2, 10, animations);
    AnimationComponent::addAnimationToVector("right", 2, 10, animations);
    AnimationComponent::addAnimationToVector("up", 2, 10, animations);
    commandPrompt->addComponent(new AnimationComponent("/interface/arrowkeys.png", 16, animations));
    commandPrompt->setPos(
        entity->pos().x() + (entity->getSize().width() - commandPrompt->getSize().width()) / 2,
        entity->pos().y() - 1.5 * commandPrompt->getSize().height());
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

void InteractiveComponent::onIntersect(HitboxComponent *hb)
{
    InteractiveHitboxComponent* ihb = static_cast<InteractiveHitboxComponent*> (hb);
    showPrompt();
    ihb->askKey(key);
    if (readyToInteract && ihb->isActive())
    {
        this->action(hb->getEntity());
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
