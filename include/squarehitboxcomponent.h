#ifndef SQUAREHITBOXCOMPONENT_H
#define SQUAREHITBOXCOMPONENT_H

#include "hitboxcomponent.h"

class CircularHitboxComponent;

class SquareHitboxComponent : public HitboxComponent
{
public:
    SquareHitboxComponent(QString name_ = "HitboxComponent")
        :HitboxComponent(name_) {}

    void init() override;

    void setSize(const QSizeF& hitbox_);
    void setSize(float w, float h);
    QSizeF& getSize() {return size;}

    QRectF getHitbox() const;

    bool intersects(HitboxComponent *hitbox) const override;

protected:
    QSizeF size;
};

#include "circlehitboxcomponent.h"

#endif // SQUAREHITBOXCOMPONENT_H
