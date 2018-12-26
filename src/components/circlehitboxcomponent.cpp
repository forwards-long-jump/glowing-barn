#include "include/circlehitboxcomponent.h"
#include <QtCore/qmath.h>


void CircleHitboxComponent::init()
{
    setOffset(0, 0);
    setRadius(sqrt(entity->getSize().width() * entity->getSize().width()
                 + entity->getSize().height() * entity->getSize().height()) / 2);
}

bool CircleHitboxComponent::intersects(HitboxComponent *hitbox) const
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
