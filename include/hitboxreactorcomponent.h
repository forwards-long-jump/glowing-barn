#ifndef HITBOXREACTORCOMPONENT_H
#define HITBOXREACTORCOMPONENT_H

#include "component.h"
#include "hitboxcomponent.h"

/**
 * Hitbox which reacts to intersection with a specified type of hitboxes
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class HitboxReactorComponent : public Component
{
public:
    HitboxReactorComponent(QString targetName_, QString name_ = "HitboxReactorComponent")
        :Component(name_),
        targetName(targetName_) {}

    void update() override;

    void setHitbox(HitboxComponent* hb);

    virtual void onIntersect(HitboxComponent* hb) = 0;

protected:
    QString targetName;
    HitboxComponent* hitbox;
};

#endif // HITBOXREACTORCOMPONENT_H
