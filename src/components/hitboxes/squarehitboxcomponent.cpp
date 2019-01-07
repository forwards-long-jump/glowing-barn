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

QPointF SquareHitboxComponent::getCenter() const
{
    return parent->pos() + getOffset() + QPointF(size.width() / 2, size.height() / 2);
}

QRectF SquareHitboxComponent::getHitbox() const
{
    return QRectF(parent->pos() + offset, size);
}

bool SquareHitboxComponent::intersects(HitboxComponent *hitbox) const
{
    SquareHitboxComponent* square = dynamic_cast<SquareHitboxComponent*> (hitbox);
    if (square)
    {
        return getHitbox().intersects(square->getHitbox());
    }

    CircleHitboxComponent* circle = dynamic_cast<CircleHitboxComponent*> (hitbox);
    {
        // here intersects is a misnomer
        // but cases in which it is used as such are where
        // the rectangular one is way smaller than the circular one
        QPointF vectD = circle->getCenter() - getCenter();
        return (sqrt(QPointF::dotProduct(vectD, vectD)) <= circle->getRadius());
    }
}
