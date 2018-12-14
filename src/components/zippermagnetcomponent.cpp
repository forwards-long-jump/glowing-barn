#include "zippermagnetcomponent.h"
#include <QDebug>

/**
 * @brief The name that will be used everywhere to identify the associated HitboxComponent
 */
const QString ZipperMagnetComponent::HITBOX_NAME = "ZipperMagnetHitbox";

/**
 * @brief ZipperMagnetComponent::ZipperMagnetComponent
 * @param direction
 * @param hitboxSize
 * @param speed
 */
ZipperMagnetComponent::ZipperMagnetComponent(DIRECTION direction_, QSizeF hitboxSize_, float speed_) : Component("ZipperMagnetComponent")
{
    hitboxSize = hitboxSize_;
    direction = direction_;
    speed = speed_;
}

/**
 * @brief Create an HitboxComponent, attach it to the current entity and set its size
 */
void ZipperMagnetComponent::init()
{
    HitboxComponent *hc = new HitboxComponent(HITBOX_NAME);
    getEntity()->addComponent(hc);

    QPointF entityCenter(getEntity()->getSize().width() / 2, getEntity()->getSize().height() / 2);
    QRectF hitboxRect;
    //hc->setOffset(-500, -500);
    // TODO: Fix hitbox position

    switch(direction)
    {
    case DIRECTION::RIGHT:
        hitboxRect.setCoords(
                    entityCenter.x(), entityCenter.y() - (getEntity()->getSize().height() + hitboxSize.height()) / 2,
                    hitboxSize.width(), hitboxSize.height());
        break;
    case DIRECTION::LEFT:
        hitboxRect.setCoords(
                    entityCenter.x() - hitboxSize.width(), entityCenter.y() - (getEntity()->getSize().height() + hitboxSize.height()) / 2,
                    entityCenter.x(), hitboxSize.height());
        break;
    case DIRECTION::DOWN:
        hitboxRect.setCoords(
                    entityCenter.y() - (getEntity()->getSize().height() + hitboxSize.height()) / 2, entityCenter.x(),
                    hitboxSize.height(), hitboxSize.width());
        break;
    case DIRECTION::UP:
        hitboxRect.setCoords(
                    entityCenter.y() - (getEntity()->getSize().height() + hitboxSize.height()) / 2, entityCenter.x() - hitboxSize.width(),
                    hitboxSize.height(), entityCenter.x());
        break;
    }

    hc->setOffset(hitboxRect.x(), hitboxRect.y());
    hc->setSize(hitboxRect.width(), hitboxRect.height());
}

/**
 * @brief ZipperMagnetComponent::getSpeed
 * @return
 */
float ZipperMagnetComponent::getSpeed() const
{
    return speed;
}

/**
 * @brief ZipperMagnetComponent::getDirection
 * @return
 */
ZipperMagnetComponent::DIRECTION ZipperMagnetComponent::getDirection() const
{
    return direction;
}

void ZipperMagnetComponent::update() {}

// TODO: Remove hitbox component on detach
