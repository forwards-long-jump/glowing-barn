#include <QtCore/qmath.h>

#include "squarehitboxcomponent.h"

/**
 * @brief SquareHitboxComponent::SquareHitboxComponent
 * @param name_
 */
SquareHitboxComponent::SquareHitboxComponent(QString name_)
    :HitboxComponent(name_) {}

/**
 * @brief SquareHitboxComponent::init
 */
void SquareHitboxComponent::init()
{
    setOffset(0, 0);
    setSize(parent->getSize());
}

/**
 * @brief SquareHitboxComponent::setSize
 * @param hitbox_
 */
void SquareHitboxComponent::setSize(const QSizeF &hitbox_)
{
    size = hitbox_;
}

/**
 * @brief SquareHitboxComponent::setSize
 * @param width
 * @param height
 */
void SquareHitboxComponent::setSize(float w, float h)
{
    setSize(QSizeF(w, h));
}

/**
 * @brief SquareHitboxComponent::getCenter
 * @return
 */
QPointF SquareHitboxComponent::getCenter() const
{
    return parent->pos() + getOffset() + QPointF(size.width() / 2, size.height() / 2);
}

/**
 * @brief SquareHitboxComponent::getHitbox
 * @return
 */
QRectF SquareHitboxComponent::getHitbox() const
{
    return QRectF(parent->pos() + offset, size);
}

/**
 * @brief SquareHitboxComponent::intersects
 * Note that this method is a misnomer when given a CircleHitboxComponent as argument,
 * in which case it return true when its center is contained by the circle
 *
 * @param hitbox
 * @return
 */
bool SquareHitboxComponent::intersects(HitboxComponent *hitbox) const
{
    SquareHitboxComponent* square = dynamic_cast<SquareHitboxComponent*> (hitbox);
    if (square)
    {
        return getHitbox().intersects(square->getHitbox());
    }

    CircleHitboxComponent* circle = dynamic_cast<CircleHitboxComponent*> (hitbox);
    {
        QPointF vectD = circle->getCenter() - getCenter();
        return (sqrt(QPointF::dotProduct(vectD, vectD)) <= circle->getRadius());
    }
}
