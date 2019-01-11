#include "magnetjumpercomponent.h"

const QString MagnetJumperComponent::HITBOX_NAME = "MagnetJumperHitbox";
MagnetJumperComponent::MagnetJumperComponent(float speed_, float rotation_, QString requiredButtons_) : Component("MagnetJumperComponent")
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
    force = speed_;
    rotation = rotation_;
}

void MagnetJumperComponent::init()
{
    SquareHitboxComponent* hc = new SquareHitboxComponent(HITBOX_NAME);
    getParent()->addComponent(hc);
}

float MagnetJumperComponent::getForce() const
{
    return force;
}

float MagnetJumperComponent::getRotation() const
{
    return rotation;
}

bool MagnetJumperComponent::isDisabled() const
{
    return disabled;
}

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
