#ifndef MAGNETREACTORCOMPONENT_H
#define MAGNETREACTORCOMPONENT_H

#include "hitboxreactorcomponent.h"
#include "physicscomponent.h"
#include "magnetzippercomponent.h"
#include "playerinputcomponent.h"

/**
 * Allows its entity to react to MagnetZipperComponents
 *
 * @authors Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret
 */

class MagnetZipperReactorComponent : public HitboxReactorComponent
{
public:
    MagnetZipperReactorComponent(QString name = "MagnetZipperReactorComponent");

    void init() override;
    void onIntersect(HitboxComponent* hitboxComponent) override;
    void onEnable() override;
    void onDisable() override;
    void update() override;


    MagnetZipperComponent::DIRECTION getCurrentDirection() const;

private:
    const float ZIPPER_FRICTION = 0.7;
    const float ZIPPER_DISTANCE_ACCELERATION = 0.1;

    void handleZipperMagnet(SquareHitboxComponent* hitboxComponent);

    float zipperDx = 0, zipperDy = 0;
    bool zipperFirstEntrance = false;
    bool isInAnyField = false;
    MagnetZipperComponent::DIRECTION currentDirection;

};

#endif // MAGNETREACTORCOMPONENT_H
