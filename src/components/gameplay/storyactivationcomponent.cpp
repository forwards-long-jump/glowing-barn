#include "storyactivationcomponent.h"

StoryActivationComponent::StoryActivationComponent(QString buttonName)
    :GameButtonComponent(buttonName, true, false, 1, false, "", "", "InteractiveHitboxComponent")
{

}

void StoryActivationComponent::update()
{
    GameButtonComponent::update();
    //commandPrompt->disableComponent("AnimationComponent");
}

void StoryActivationComponent::action(Entity *target)
{
    GameButtonComponent::action(target);

    target->setPos(parent->pos() + QPointF(-4, -24));
    static_cast<AnimationComponent*>(target->getComponent("AnimationComponent"))->setCurrentAnimation("standing");
    static_cast<AnimationComponent*>(target->getComponent("AnimationComponent"))->setRotation(0);

    //target->disableComponent("PlayerInputComponent");
    target->disableComponent("MagnetParticleSpawner");
    target->disableComponent("PhysicsComponent");
    //target->setPos();
}
