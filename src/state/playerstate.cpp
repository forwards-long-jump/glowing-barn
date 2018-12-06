#include "include/playerstate.h"

StandingState PlayerState::standing;
RunningState PlayerState::running;
SkiddingState PlayerState::skidding;
JumpingState PlayerState::jumping;
FallingState PlayerState::falling;
ZippingState PlayerState::zipping;
bool PlayerState::headingRight = true;


bool PlayerState::handleHorizontalMovement(PlayerInputComponent *playerInputComponent)
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        physicsComponent->setLeft(Game::input.isKeyDown(Input::LEFT));
        physicsComponent->setRight(Game::input.isKeyDown(Input::RIGHT));
    }

    if (Game::input.isKeyDown(Input::LEFT))
    {
        headingRight = false;
    }
    else if (Game::input.isKeyDown(Input::RIGHT))
    {
        headingRight = true;
    }
    else
    {
        return true;
    }
    return false;
}

bool PlayerState::checkFalling(PlayerInputComponent *playerInputComponent) const
{
    PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*> (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr && physicsComponent->isFalling())
    {
        playerInputComponent->setState(&PlayerState::falling);
    }
}

void PlayerState::enter(PlayerInputComponent *playerInputComponent) const
{
    Component* physicsComponent = (playerInputComponent->getEntity()->getComponent("PhysicsComponent"));
    if (physicsComponent != nullptr)
    {
        dynamic_cast<PhysicsComponent*> (physicsComponent)->setFriction(friction);
    }
}

void ZippingState::handleInput(PlayerInputComponent* playerInputComponent)
{
    // nothing yet
}
