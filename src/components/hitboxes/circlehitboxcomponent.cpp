#include "include/circlehitboxcomponent.h"
#include <QtCore/qmath.h>


void CircleHitboxComponent::init()
{
    setOffset(parent->getSize().width() / 2, parent->getSize().height() / 2);
    setRadius(sqrt(parent->getSize().width() * parent->getSize().width()
                 + parent->getSize().height() * parent->getSize().height()) / 2);
}

bool CircleHitboxComponent::intersects(HitboxComponent* hitbox) const
{
     QPointF vectD = hitbox->getCenter() - getCenter();
     return (sqrt(QPointF::dotProduct(vectD, vectD)) <= radius);
}

void CircleHitboxComponent::setRadius(float radius_)
{
    radius = radius_;
}

float CircleHitboxComponent::getRadius() const
{
    return radius;
}
