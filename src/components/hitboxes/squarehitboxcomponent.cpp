#include "squarehitboxcomponent.h"
#include <QtCore/qmath.h>

void SquareHitboxComponent::init()
{
    setOffset(0, 0);
    setSize(parent->getSize());
}

void SquareHitboxComponent::setSize(const QSizeF &hitbox_)
{
    size = hitbox_;
}

void SquareHitboxComponent::setSize(float w, float h)
{
    setSize(QSizeF(w, h));
}

QRectF SquareHitboxComponent::getHitbox() const
{
    return QRectF(parent->pos() + offset, size);
}

bool SquareHitboxComponent::intersects(HitboxComponent* hitbox) const
{
    SquareHitboxComponent* square = dynamic_cast<SquareHitboxComponent*> (hitbox);
    if (square)
        return getHitbox().intersects(square->getHitbox());


     CircleHitboxComponent* circle = dynamic_cast<CircleHitboxComponent*> (hitbox);
     if (circle)
     {
         QPointF vectD = circle->getCenter() - getCenter();
         return (sqrt(QPointF::dotProduct(vectD, vectD)) <= circle->getRadius());
     }
}
