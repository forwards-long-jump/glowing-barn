#include "playerstate.h"

void DeadState::handleInput(PlayerInputComponent* playerInputComponent)
{

}

void DeadState::enter(PlayerInputComponent* playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getParent()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        physicsComponent->setLeft(false);
        physicsComponent->setRight(false);
    }

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(playerInputComponent->getParent()->getComponent("AnimationComponent"));
    if(ac)
    {
        ac->setCurrentAnimation("death");
        ac->disableLooping();
    }
}

void DeadState::setHeadingRight(bool headingRight_, PlayerInputComponent* playerInputComponent)
{

}
