#ifndef HURTREACTORCOMPONENT_H
#define HURTREACTORCOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "gamescene.h"

/**
 * Restarts the current map on contact with a HurtComponent
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class HurtReactorComponent : public HitboxReactorComponent
{
public:
    HurtReactorComponent(bool resetMap = true, QString name = "HurtReactorComponent");
    const static QString HITBOX_REACTOR_NAME;

    void init() override;
    void onIntersect(HitboxComponent* hitboxComponent) override;
    bool isDead() const;

private:
    bool resetMap = false;
    bool died = false;
};

#endif // HURTREACTORCOMPONENT_H
