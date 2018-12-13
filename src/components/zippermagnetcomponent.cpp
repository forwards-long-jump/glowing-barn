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

    QPointF entityCenter(getEntity()->x() + getEntity()->getSize().width() / 2, getEntity()->y() + getEntity()->getSize().height() / 2);
    QRectF hitboxRect;
    // TODO: Fix hitbox position
/*
    switch(direction)
    {
    case DIRECTION::RIGHT:
        hitboxRect.setCoords(entityCenter.x(), entityCenter.y() - hitboxSize.height() / 2,
                             entityCenter.x() + hitboxSize.width(), entityCenter.y() + hitboxSize.height() / 2);
        break;
    case DIRECTION::LEFT:
        hitboxRect.setCoords(entityCenter.x() - hitboxSize.width(), entityCenter.y() - hitboxSize.height() / 2,
                             entityCenter.x(), entityCenter.y() + hitboxSize.height() / 2);
        break;
    case DIRECTION::UP:
        hitboxRect.setCoords(entityCenter.x() - hitboxSize.width() / 2, entityCenter.y() - hitboxSize.height(),
                             entityCenter.x() + hitboxSize.width() / 2, entityCenter.y());
        break;
    case DIRECTION::DOWN:
        hitboxRect.setCoords(entityCenter.x() - hitboxSize.width() / 2, entityCenter.y(),
                             entityCenter.x() + hitboxSize.width() / 2, entityCenter.y() + hitboxSize.height());
        break;
    }

    hc->setOffset(hitboxRect.width() -getEntity()->pos().x(), hitboxRect.height() - getEntity()->pos().y());
    hc->setSize(hitboxRect.width(), hitboxRect.height());*/
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
