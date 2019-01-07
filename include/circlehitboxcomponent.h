#ifndef CIRCLEHITBOXCOMPONENT_H
#define CIRCLEHITBOXCOMPONENT_H


#include "hitboxcomponent.h"

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
