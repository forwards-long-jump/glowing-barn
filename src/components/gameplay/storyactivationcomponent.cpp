#include "storyactivationcomponent.h"

/**
 * @brief StoryActivationComponent::StoryActivationComponent
 * @param buttonName
 */
StoryActivationComponent::StoryActivationComponent(QString buttonName)
    : GameButtonComponent(buttonName, true)
{

}

/**
 * @brief StoryActivationComponent::update
 */
void StoryActivationComponent::update()
{
    GameButtonComponent::update();
}

/**
 * @brief StoryActivationComponent::action
 * @param target
 */
void StoryActivationComponent::action(Entity *target)
{
    GameButtonComponent::action(target);

    target->setPos(parent->pos() + QPointF(-4, -24));
    static_cast<AnimationComponent*>(target->getComponent("AnimationComponent"))->setCurrentAnimation("standing");
    static_cast<AnimationComponent*>(target->getComponent("AnimationComponent"))->setRotation(0);

    target->disableComponent("MagnetParticleSpawner");
    target->disableComponent("PhysicsComponent");
}
