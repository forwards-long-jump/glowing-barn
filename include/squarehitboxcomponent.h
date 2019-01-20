#ifndef SQUAREHITBOXCOMPONENT_H
#define SQUAREHITBOXCOMPONENT_H


#include "hitboxcomponent.h"

class CircularHitboxComponent;

/**
 * Hitbox whose shape is rectangular
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class SquareHitboxComponent : public HitboxComponent
{
public:
    SquareHitboxComponent(QString name_ = "HitboxComponent");

    void init() override;

    QPointF getCenter() const override;
    void setSize(const QSizeF& hitbox_);
    void setSize(float w, float h);
    QSizeF& getSize() {return size;}

    QRectF getHitbox() const;

    bool intersects(HitboxComponent *hitbox) const override;

protected:
    QSizeF size;
};

#include "circlehitboxcomponent.h"
#include <QtCore/qmath.h>

#endif // SQUAREHITBOXCOMPONENT_H
