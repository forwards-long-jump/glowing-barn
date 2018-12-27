#ifndef MAGNETREACTORCOMPONENT_H
#define MAGNETREACTORCOMPONENT_H

#include "component.h"
#include "squarehitboxcomponent.h"
#include "physicscomponent.h"
#include "zippermagnetcomponent.h"
#include "playerinputcomponent.h"

class MagneticFieldReactorComponent : public Component
{
public:
    MagneticFieldReactorComponent();
    void update() override;
    void onEnable() override;

private:
    void handleZipperMagnet(SquareHitboxComponent *hitboxComponent);
    const float ZIPPER_FRICTION = 0.7;
    const float ZIPPER_DISTANCE_ACCELERATION = 0.1;
    void handleZipperMagnet(HitboxComponent *hitboxComponent);
    float zipperDx, zipperDy;
    bool zipperFirstEntrance;

};

#endif // MAGNETREACTORCOMPONENT_H
