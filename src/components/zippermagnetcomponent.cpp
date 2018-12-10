#include "zippermagnetcomponent.h"
#include <QDebug>

// TODO: Add hitbox component on attach
// #include "hitboxcomponent.h"

ZipperMagnetComponent::ZipperMagnetComponent(DIRECTION direction_, QSizeF hitboxSize, float speed_) : Component("ZipperMagnetComponent")
{
    // TODO HitboxComponent *hc = new HitboxComponent();
    // TODO getEntity()->addComponent(hc);
    // TODO: Do this on compononent init and use entity instead

   // QPointF entityCenter(getEntity()->x() + getEntity()->getSize().width() / 2, getEntity()->y() + getEntity()->getSize().height() / 2);
    QPointF entityCenter(100 + 15, 700 + 15);
    QRectF hitboxRect;

    switch(direction_)
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

    // TODO hc->setRectangle(hitboxRect);
    DEBUGRectangle = hitboxRect;
    direction = direction_;
    speed = speed_;
}

float ZipperMagnetComponent::getSpeed() const
{
    return speed;
}

ZipperMagnetComponent::DIRECTION ZipperMagnetComponent::getDirection() const
{
    return direction;
}

void ZipperMagnetComponent::update()
{

}

// TODO: Remove hitbox component on detach
