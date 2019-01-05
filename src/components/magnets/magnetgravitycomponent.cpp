#include "magnetgravitycomponent.h"

const QString MagnetGravityComponent::HITBOX_NAME = "MagnetGravityHitbox";
MagnetGravityComponent::MagnetGravityComponent(float radius_, float force_, QString requiredButtons_) : Component("MagnetGravityComponent")
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
    radius = radius_;
    force = force_;
}

void MagnetGravityComponent::init()
{
    CircleHitboxComponent *hc = new CircleHitboxComponent(HITBOX_NAME);
    getEntity()->addComponent(hc);
    hc->setRadius(radius);
}

float MagnetGravityComponent::getForce() const
{
    return force;
}

void MagnetGravityComponent::update() {
    if(requiredButtons.length() > 0)
    {
        if(GameButtonComponent::areButtonsPressed(requiredButtons))
        {
            getEntity()->enableComponent(HITBOX_NAME);
        }
        else
        {
            getEntity()->disableComponent(HITBOX_NAME);
        }
    }
}

