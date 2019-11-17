#include "playerinputcomponent.h"

/**
 * @brief PlayerInputComponent::PlayerInputComponent
 * @param name_
 */
PlayerInputComponent::PlayerInputComponent(QString name_)
    :Component(name_) {}

/**
 * @brief PlayerInputComponent::update
 */
void PlayerInputComponent::update()
{
    DebugComponent* d = dynamic_cast<DebugComponent*>(parent->getComponent("DebugComponent"));
    if(d) {
        if (state == &PlayerState::standing)
        {
            d->setDebugText("standing");
        }
        if (state == &PlayerState::running)
        {
            d->setDebugText("running");
        }
        if (state == &PlayerState::skidding)
        {
            d->setDebugText("skidding");
        }
        if (state == &PlayerState::jumping)
        {
            d->setDebugText("jumping");
        }
        if (state == &PlayerState::falling)
        {
            d->setDebugText("falling");
        }
        if (state == &PlayerState::zipping)
        {
            d->setDebugText("zipping");
        }
    }

    handleMagnetActivation();

    // Handle contextual interactions
    interactiveHitbox.setActive(Game::input.isKeyDown(interactiveHitbox.getAskedKey()));

    AnimationComponent* ac = dynamic_cast<AnimationComponent*>(getParent()->getComponent("AnimationComponent"));
    PhysicsComponent* pc = dynamic_cast<PhysicsComponent*>(getParent()->getComponent("PhysicsComponent"));

    if(ac && pc && getState() != &PlayerState::zipping)
    {
        int targetRotation = -qAbs(pc->getSpeed().x());
        ac->setRotation(ac->getRotation() + (targetRotation - ac->getRotation()) * 0.5);
    }

    state->handleInput(this);
}

/**
 * @brief PlayerInputComponent::handleMagnetActivation
 */
void PlayerInputComponent::handleMagnetActivation()
{
    if(Game::input.isKeyDown(Input::ZIP))
    {
        if(releasedKeyAfterTogglingMagnet)
        {
            releasedKeyAfterTogglingMagnet = false;
            // Toggle all magnetic components here
            // NOTE: We mostly use the magnetZipper to check if any magnet is enabled
            if(!parent->disableComponent("MagnetZipperReactorComponent"))
            {
                if(parent->enableComponent("MagnetZipperReactorComponent")) {
                    static_cast<AnimationComponent*>(parent->getComponent("AnimationComponent"))->setImage(QPixmap(":/entities/player.png"));
                }
            }
            else {
                static_cast<AnimationComponent*>(parent->getComponent("AnimationComponent"))->setImage(QPixmap(":/entities/player-deactivated.png"));
            }

            if(!parent->disableComponent("MagnetJumperReactorComponent")) parent->enableComponent("MagnetJumperReactorComponent");
            if(!parent->disableComponent("MagnetGravityReactorComponent")) parent->enableComponent("MagnetGravityReactorComponent");
            // Player magnet sources
            if(!parent->disableComponent("PlayerGravityMagnet")) parent->enableComponent("PlayerGravityMagnet");
        }
    }
    else
    {
        releasedKeyAfterTogglingMagnet = true;
    }
}


/**
 * @brief PlayerInputComponent::init
 */
void PlayerInputComponent::init()
{
    interactiveHitbox.setParent(parent);
    interactiveHitbox.init();
    setState(&PlayerState::standing);
}

/**
 * @brief PlayerInputComponent::getState
 * @return
 */
PlayerState* PlayerInputComponent::getState() const
{
    return state;
}

/**
 * @brief PlayerInputComponent::setState
 * Changes state and calls the new state's enter method
 * @param _state
 */
void PlayerInputComponent::setState(PlayerState* _state)
{
    if(state != _state)
    {
        state = _state;
        state->enter(this);
    }
}

/**
 * @brief PlayerInputComponent::onDisable
 */
void PlayerInputComponent::onDisable()
{
    PhysicsComponent* pc = static_cast<PhysicsComponent*>(getParent()->getComponent("PhysicsComponent"));
    pc->setLeft(false);
    pc->setRight(false);
}
