#ifndef MAGNETREACTORCOMPONENT_H
#define MAGNETREACTORCOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "physicscomponent.h"
#include "magnetzippercomponent.h"
#include "playerinputcomponent.h"

class MagnetZipperReactorComponent : public HitboxReactorComponent
{
public:
    MagnetZipperReactorComponent(QString name = "MagnetZipperReactorComponent");

    void init() override;
    void onIntersect(HitboxComponent* hitboxComponent) override;
    void onEnable() override;
    void update() override;


    MagnetZipperComponent::DIRECTION getCurrentDirection() const;

private:
    const float ZIPPER_FRICTION = 0.7;
    const float ZIPPER_DISTANCE_ACCELERATION = 0.1;

    void handleZipperMagnet(SquareHitboxComponent *hitboxComponent);

    float zipperDx, zipperDy;
    bool zipperFirstEntrance;
    bool isInAnyField;
    MagnetZipperComponent::DIRECTION currentDirection;

};

#endif // MAGNETREACTORCOMPONENT_H
