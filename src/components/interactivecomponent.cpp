#include "include/interactivecomponent.h"

InteractiveComponent::InteractiveComponent(Input::Key key_, QString name_)
    :HitboxReactorComponent("InteractiveHitboxComponent", name_),
    key(key_)
{
    readyToInteract = false;
    removePromptOnNextTick = false;

    //commandPrompt = new GraphicsComponent("CommandPromptComponent");
    commandPrompt = new DebugComponent(Qt::white);
}

void InteractiveComponent::init()
{
    HitboxReactorComponent::init();
    entity->addComponent(commandPrompt);
    entity->disableComponent("DebugComponent");
}

void InteractiveComponent::update()
{
    HitboxReactorComponent::update();
    if (removePromptOnNextTick)
    {
        entity->disableComponent("DebugComponent");
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
    entity->enableComponent("DebugComponent");
}
