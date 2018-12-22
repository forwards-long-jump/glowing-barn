#ifndef HITBOXREACTORCOMPONENT_H
#define HITBOXREACTORCOMPONENT_H

#include "component.h"
#include "hitboxcomponent.h"

class HitboxReactorComponent : public Component
{
public:
    HitboxReactorComponent(QString targetName_, QString name_ = "HitboxReactorComponent")
        :Component(name_),
        targetName(targetName_) {}

    void update() override;
    void init() override;

    void setHitboxOffset(float dx, float dy);
    void setHitboxSize(float w, float h);

    virtual void onIntersect(HitboxComponent* hb) = 0;

protected:
    QString targetName;
    HitboxComponent hitbox;
};

#endif // HITBOXREACTORCOMPONENT_H
