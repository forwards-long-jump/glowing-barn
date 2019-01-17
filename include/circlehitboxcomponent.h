#ifndef CIRCLEHITBOXCOMPONENT_H
#define CIRCLEHITBOXCOMPONENT_H


#include "hitboxcomponent.h"

/**
 * HitboxComponent whose shape is a circle
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class CircleHitboxComponent : public HitboxComponent
{
public:
    CircleHitboxComponent(QString name_ = "HitboxComponent")
        :HitboxComponent(name_) {}

    void init() override;

    QPointF getCenter() const override;
    void setRadius(float radius);
    void offsetOffset(QPointF offset);
    float getRadius() const;

    bool intersects(HitboxComponent *hitbox) const override;

protected:
    float radius;
};

#endif // CIRCLEHITBOXCOMPONENT_H
