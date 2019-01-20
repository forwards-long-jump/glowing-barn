#include "magnetgravitycomponent.h"

const QString MagnetGravityComponent::HITBOX_NAME = "MagnetGravityHitbox";

/**
 * @brief MagnetGravityComponent::MagnetGravityComponent
 * @param radius_
 * @param force_ Negative value for attractive magnet, positive for repulsive
 * @param requiredButtons_
 * @param hitboxOffset_
 * @param customHitboxName
 * @param name
 */
MagnetGravityComponent::MagnetGravityComponent(float radius_, float force_, QString requiredButtons_, QPointF hitboxOffset_, QString customHitboxName, QString name)
    : Component(name)
{
    requiredButtons = GameButtonComponent::getButtonVectorFromString(requiredButtons_);
    radius = radius_;
    force = force_;
    hitboxName = customHitboxName;
    hitboxOffset = hitboxOffset_;
}

/**
 * @brief MagnetGravityComponent::init
 */
void MagnetGravityComponent::init()
{
    CircleHitboxComponent* hc = new CircleHitboxComponent(hitboxName);
    getParent()->addComponent(hc);
    hc->setRadius(radius);
    if(!hitboxOffset.isNull())
    {
        hc->setOffset(hc->getOffset() + hitboxOffset);
    }
}

/**
 * @brief MagnetGravityComponent::onEnable
 */
void MagnetGravityComponent::onEnable()
{
    getParent()->enableComponent(hitboxName);
}

/**
 * @brief MagnetGravityComponent::onDisable
 */
void MagnetGravityComponent::onDisable()
{
    getParent()->disableComponent(hitboxName);
}

/**
 * @brief MagnetGravityComponent::getForce
 * @return
 */
float MagnetGravityComponent::getForce() const
{
    return force;
}

/**
 * @brief MagnetGravityComponent::getDisabledTime
 * @return
 */
int MagnetGravityComponent::getDisabledTime() const
{
    return ticksDisabled;
}

/**
 * @brief MagnetGravityComponent::update
 */
void MagnetGravityComponent::update() {
    if(requiredButtons.length() > 0)
    {
        if(GameButtonComponent::areButtonsPressed(requiredButtons))
        {
            getParent()->enableComponent(HITBOX_NAME);
            ticksDisabled -= 2;
            if(ticksDisabled > 50) ticksDisabled = 50;
            if(ticksDisabled < 0)  ticksDisabled = 0;
        }
        else
        {
            getParent()->disableComponent(HITBOX_NAME);
            ticksDisabled++;
        }
    }
}
