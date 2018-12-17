#ifndef MAGNETREACTORCOMPONENT_H
#define MAGNETREACTORCOMPONENT_H

#include "component.h"
#include "hitboxcomponent.h"
#include "physicscomponent.h"
#include "zippermagnetcomponent.h"
#include "playerinputcomponent.h"

class MagneticFieldReactorComponent : public Component
{
public:
    MagneticFieldReactorComponent();
    void update() override;
private:
    void handleZipperMagnet(HitboxComponent *hitboxComponent);

};

#endif // MAGNETREACTORCOMPONENT_H
