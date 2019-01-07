#include "circlehitboxcomponent.h"
#include "squarehitboxcomponent.h"

#include <QtCore/qmath.h>

#include "QGraphicsItem"


void CircleHitboxComponent::init()
{
    setRadius(sqrt(parent->getSize().width() * parent->getSize().width()
                 + parent->getSize().height() * parent->getSize().height()) / 2);
    QPointF center(parent->getSize().width() / 2,
                   parent->getSize().height() / 2);
    setOffset(center.x() - radius, center.y() - radius);
}

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
        // here intersects is a misnomer
        // but cases in which it is used as such are where
        // the rectangular one is way smaller than the circular one
        return d <= radius;
    }
}

/**
 * @brief CircleHitboxComponent::offsetOffset use to offset the offset
 * @param offset
 */
void CircleHitboxComponent::offsetOffset(QPointF offset)
{
    setOffset(this->offset.x() + offset.x(), this->offset.y() + offset.y());
}

QPointF CircleHitboxComponent::getCenter() const
{
    return parent->pos() + getOffset() + QPointF(radius, radius);
}

void CircleHitboxComponent::setRadius(float radius)
{
    this->radius = radius;
    QPointF center(parent->getSize().width() / 2,
                   parent->getSize().height() / 2);
    setOffset(center.x() - radius, center.y() - radius);
}

float CircleHitboxComponent::getRadius() const
{
    return radius;
}
