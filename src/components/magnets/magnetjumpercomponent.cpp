#include "magnetjumpercomponent.h"

const QString MagnetJumperComponent::HITBOX_NAME = "MagnetJumperHitbox";

/**
 * @brief MagnetJumperComponent::MagnetJumperComponent
 * @param speed_ speed of the jump it gives the player
 * @param rotation_
 * @param requiredButtons_
 */
MagnetJumperComponent::MagnetJumperComponent(float speed_, float rotation_, QString requiredButtons_)
    : Component("MagnetJumperComponent")
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
    force = speed_;
    rotation = rotation_;
}

/**
 * @brief MagnetJumperComponent::init
 */
void MagnetJumperComponent::init()
{
    SquareHitboxComponent* hc = new SquareHitboxComponent(HITBOX_NAME);
    getParent()->addComponent(hc);
}

/**
 * @brief MagnetJumperComponent::getForce
 * @return
 */
float MagnetJumperComponent::getForce() const
{
    return force;
}

/**
 * @brief MagnetJumperComponent::getRotation
 * @return
 */
float MagnetJumperComponent::getRotation() const
{
    return rotation;
}

/**
 * @brief MagnetJumperComponent::isDisabled
 * @return
 */
bool MagnetJumperComponent::isDisabled() const
{
    return disabled;
}

/**
 * @brief MagnetJumperComponent::update
 */
void MagnetJumperComponent::update() {
    if(requiredButtons.length() > 0)
    {
        if(GameButtonComponent::areButtonsPressed(requiredButtons))
        {
            getParent()->enableComponent(HITBOX_NAME);
            disabled = false;
        }
        else
        {
            getParent()->disableComponent(HITBOX_NAME);
            disabled = true;
        }
    }
}
