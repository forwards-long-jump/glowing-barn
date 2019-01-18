#include "circlehitboxcomponent.h"
#include "squarehitboxcomponent.h"

#include <QtCore/qmath.h>

#include "QGraphicsItem"

/**
 * @brief CircleHitboxComponent::CircleHitboxComponent
 * @param name_
 */
CircleHitboxComponent::CircleHitboxComponent(QString name_)
    :HitboxComponent(name_) {}

/**
 * @brief CircleHitboxComponent::init
 * Sets the hitbox as the escribed center of the entity
 */
void CircleHitboxComponent::init()
{
    setRadius(sqrt(parent->getSize().width() * parent->getSize().width()
                 + parent->getSize().height() * parent->getSize().height()) / 2);
    QPointF center(parent->getSize().width() / 2,
                   parent->getSize().height() / 2);
    setOffset(center.x() - radius, center.y() - radius);
}


/**
 * @brief CircleHitboxComponent::intersects
 * Note that this method is a misnomer when given a SquareHitboxComponent as argument,
 * in which case it return true when it contains the argument's center
 * @param hitbox
 * @return
 */
bool CircleHitboxComponent::intersects(HitboxComponent* hitbox) const
{
    QPointF vectD = hitbox->getCenter() - getCenter();
    float d = sqrt(QPointF::dotProduct(vectD, vectD));
    CircleHitboxComponent* circle = dynamic_cast<CircleHitboxComponent*> (hitbox);
    if (circle)
    {
        return d <= circle->getRadius() + radius;
    }
    else
    {
        return d <= radius;
    }
}

/**
 * @brief CircleHitboxComponent::getCenter
 * @return
 */
QPointF CircleHitboxComponent::getCenter() const
{
    return parent->pos() + getOffset() + QPointF(radius, radius);
}

/**
 * @brief CircleHitboxComponent::setRadius
 * @param radius
 */
void CircleHitboxComponent::setRadius(float radius)
{
    this->radius = radius;
    QPointF center(parent->getSize().width() / 2,
                   parent->getSize().height() / 2);
    setOffset(center.x() - radius, center.y() - radius);
}

/**
 * @brief CircleHitboxComponent::getRadius
 * @return
 */
float CircleHitboxComponent::getRadius() const
{
    return radius;
}
