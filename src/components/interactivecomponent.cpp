#include "include/interactivecomponent.h"

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
    commandPrompt = new Entity(entity->parentItem(), QSizeF(8, 8));
    commandPrompt->addComponent(new DebugComponent(Qt::blue, false, false));
    commandPrompt->setPos(
        entity->pos().x() + (entity->getSize().width() - commandPrompt->getSize().width()) / 2,
        entity->pos().y() - 1.5 * commandPrompt->getSize().height());
    commandPrompt->disableComponent("DebugComponent");
}

void InteractiveComponent::update()
{
    HitboxReactorComponent::update();
    if (removePromptOnNextTick)
    {
        commandPrompt->disableComponent("DebugComponent");
    }
    removePromptOnNextTick = true;
}

void InteractiveComponent::onIntersect(HitboxComponent *hb)
{
    InteractiveHitboxComponent* ihb = static_cast<InteractiveHitboxComponent*> (hb);
    showPrompt();
    ihb->askKey(key);
    if ((readyToInteract && ihb->isActive()) || key == Input::Key::NONE)
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
    commandPrompt->enableComponent("DebugComponent");
}
