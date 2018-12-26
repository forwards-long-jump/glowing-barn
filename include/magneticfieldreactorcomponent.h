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
private:
    void handleZipperMagnet(SquareHitboxComponent *hitboxComponent);

};

#endif // MAGNETREACTORCOMPONENT_H
