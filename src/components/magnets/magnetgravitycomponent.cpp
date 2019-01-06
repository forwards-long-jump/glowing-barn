#include "magnetgravitycomponent.h"

const QString MagnetGravityComponent::HITBOX_NAME = "MagnetGravityHitbox";
MagnetGravityComponent::MagnetGravityComponent(float radius_, float force_, QString requiredButtons_, QPointF hitboxOffset_, QString customHitboxName, QString name) : Component(name)
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
    radius = radius_;
    force = force_;
    hitboxName = customHitboxName;
    hitboxOffset = hitboxOffset_;
}

void MagnetGravityComponent::init()
{
    CircleHitboxComponent* hc = new CircleHitboxComponent(hitboxName);
    getParent()->addComponent(hc);
    hc->setRadius(radius);
    if(!hitboxOffset.isNull())
    {
        hc->setOffset(hitboxOffset);
    }
}

void MagnetGravityComponent::onEnable()
{
    getParent()->enableComponent(hitboxName);
}

void MagnetGravityComponent::onDisable()
{
    getParent()->disableComponent(hitboxName);
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
            getParent()->enableComponent(HITBOX_NAME);
        }
        else
        {
            getParent()->disableComponent(HITBOX_NAME);
        }
    }
}
