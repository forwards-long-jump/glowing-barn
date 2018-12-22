#include "include/interactivecomponent.h"

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

    commandPrompt = new Entity(nullptr, 8, 8);
    entity->scene()->addItem(commandPrompt);
    commandPrompt->addComponent(new DebugComponent(Qt::blue));
    commandPrompt->setPos(
        entity->pos().x() + (entity->getSize().width() - commandPrompt->getSize().width()) / 2,
        entity->pos().y() - (entity->getSize().height() - commandPrompt->getSize().height()) / 2);
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
    commandPrompt->enableComponent("DebugComponent");
}
