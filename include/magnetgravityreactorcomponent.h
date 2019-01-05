#ifndef MAGNETGRAVITYREACTORCOMPONENT_H
#define MAGNETGRAVITYREACTORCOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "squarehitboxcomponent.h"
#include "physicscomponent.h"
#include "magnetgravitycomponent.h"
#include "playerinputcomponent.h"

class MagnetGravityReactorComponent : public HitboxReactorComponent
{
public:
    MagnetGravityReactorComponent(QString name = "MagnetGravityReactorComponent");

    void init() override;
    void onIntersect(HitboxComponent* hitboxComponent) override;

private:

};

#endif // MAGNETGRAVITYREACTORCOMPONENT_H
