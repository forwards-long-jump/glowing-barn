#include "include/circlehitboxcomponent.h"
#include <QtCore/qmath.h>
#include "QGraphicsItem"


void CircleHitboxComponent::init()
{
    setRadius(sqrt(parent->getSize().width() * parent->getSize().width()
                 + parent->getSize().height() * parent->getSize().height()) / 2);
    setOffset(-(radius/2), -(radius/2));

    new QGraphicsEllipseItem(radius, radius, this->getRadius(), this->getRadius(), parent);
}

bool CircleHitboxComponent::intersects(HitboxComponent* hitbox) const
{
     QPointF vectD = hitbox->getCenter() - getCenter();
     return (sqrt(QPointF::dotProduct(vectD, vectD)) <= radius);
}

void CircleHitboxComponent::setRadius(float radius_)
{
    radius = radius_;
    new QGraphicsEllipseItem(-(radius/2), -(radius/2), radius_, radius_, parent);
}

float CircleHitboxComponent::getRadius() const
{
    return radius;
}
